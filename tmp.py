class SarathiScheduler(BaseScheduler):

    def __init__(
        self,
        model_config: ModelConfig,
        scheduler_config: SarathiSchedulerConfig,
        cache_config: CacheConfig,
    ) -> None:
        super().__init__(model_config, scheduler_config, cache_config)
        
        # =================================================================
        # 【固定chunk_size策略】
        # 人为定好的chunk_size。如果你不想动态变更chunk_size大小，你可以固定使用这个。
        # 我们可以通过profiling等方式，在调度开始前确定好能够
        # saturate gpu computation的最大chunk_size
        # （注：在代码中，chunksize不是指prefill的chunksize，是指每次
        #  调度中，整个batch的tokens数量，也包括要做decode的tokens数）
        # =================================================================
        self.chunk_size = self.scheduler_config.chunk_size
        
        # =================================================================
        # 【动态chunk_size策略】
        # 使用动态变化的chunk_size
        # （随着调度次数增加，历史累积的要做decode的序列可能会变多，以及
        # 可能会进来更多的新请求。假设某个序列的prompt特别长，那么它就会持续占据着计算
        # 资源，影响到别的请求。所以对于这样的prompt，我们可以在迭代中逐渐减小它的preill
        # tokens数量）
        # 
        # 为了执行这个chunk_size动态变更的策略，我们需要如下4个参数:
        # 【low_chunk_size】：人为设定的最小chunk_size
        # 【high_chunk_size】: 人为设定的最大chunk_size
        # 【chunk_schedule_stages】：用于刻画调度阶段数。例如该值若等于5，则说明随着
        # 调度次数的增加，我们希望有5种逐步递减的chunk_size可以选择
        # 【chunk_schedule_max_tokens】: 这个变量比较难说明，我们直接看它怎么用。
        # 事实上，在源码中真正有意义的变量是_tokens_per_stage
        # （=chunk_schedule_max_tokens/chunk_schedule_stages）
        # 你可以理解成：对于一个正在做prefill的长序列，我们它的prefill tokens数量
        # 随着迭代阶段（stage）的增加而递减。我们设其做prefill时，每处理_tokens_per_stage
        # 个tokens就算完成了1个stage，然后就要递减一次prefill tokens。简而言之，这些
        # 参数的作用是帮助我们确定某个正在做prefill的序列当前位于哪个stage上
        # =================================================================
        self.enable_dynamic_chunking_schedule = (
            self.scheduler_config.enable_dynamic_chunking_schedule
        )
        # next four params apply only when using dynamic schedule
        self.low_chunk_size = self.scheduler_config.low_chunk_size
        self.high_chunk_size = self.scheduler_config.high_chunk_size
        self.chunk_schedule_max_tokens = self.scheduler_config.chunk_schedule_max_tokens
        self.chunk_schedule_stages = self.scheduler_config.chunk_schedule_stages

        if self.enable_dynamic_chunking_schedule:
            assert self.chunk_schedule_stages > 0
            assert self.chunk_schedule_max_tokens > 0
            assert self.low_chunk_size % 32 == 0
            assert self.high_chunk_size % 32 == 0
            # 计算在动态变更chunk_size的情况下，我们可选的chunk_size列表（详情参见相关函数注释）
            self._chunk_sizes = self._compute_chunk_size_schedule()
            # 用于计算每个stage能处理的token数（详细解释见上）
            self._tokens_per_stage = int(
                np.ceil(self.chunk_schedule_max_tokens / self.chunk_schedule_stages)
            )

    def _compute_chunk_size_schedule(self):
        # =================================================================
        # create num_steps equally spaced chunk sizes 
        # between low_chunk_size and high_chunk_size
        # 
        # self.low_chunk_size = 64
        # self.high_chunk_size = 256
        # self.chunk_schedule_stages = 5
        # 则chunk_sizes = [64, 108, 152, 196, 256]
        # 按照从大到小排序后 = [256, 196, 152, 108, 64]
        # =================================================================
        chunk_sizes = np.linspace(
            self.low_chunk_size,
            self.high_chunk_size,
            self.chunk_schedule_stages,
            dtype=np.int32,
        )[::-1]

        # =================================================================
        # 这里是调整每个备选的分块大小，让其能够被32整除
        # 这样做是考虑到tile-quantization effect，让gpu做gemm时的并行性能最大化
        # =================================================================
        round_of_chunk_sizes = min(32, self.low_chunk_size)
        chunk_sizes = (
            np.round(chunk_sizes / round_of_chunk_sizes) * round_of_chunk_sizes
        )
        chunk_sizes = chunk_sizes.astype(np.int64).tolist()

        return chunk_sizes

    def get_block_space_manager_class(self):
        return SarathiBlockSpaceManager

    def _get_seq_next_num_prefill_tokens(
        self, seq: Sequence, num_batched_tokens: int
    ) -> int:
        """
        对于一条还没做完prefill的seq，根据当前batch中已经存放的tokens数量，决定要送
        这个seq的多少tokens去做prefill
        """
        assert not seq.is_finished()
        # =================================================================
        # 如果使用动态chunk_size的方法
        # =================================================================
        if self.enable_dynamic_chunking_schedule:
            # =================================================================
            # 先计算当前seq目前一共处理了多少prefill tokens，然后根据每个阶段其最多能处理
            # 的prefill tokens数量，确定它在第几阶段（stage）
            # =================================================================
            request_stage_idx = int(
                np.ceil(seq.get_num_prompt_tokens_processed() // self._tokens_per_stage)
            )
            # =================================================================
            # 取出这个阶段的chunk_size
            # =================================================================
            assert request_stage_idx < len(self._chunk_sizes)
            chunk_size = self._chunk_sizes[request_stage_idx]
        # =================================================================
        # 如果没有使用动态变更chunk_size的策略，就用固定尺寸的chunk_size
        # （例如代码中的默认值512）
        # =================================================================
        else:
            chunk_size = self.chunk_size

        # =================================================================
        # 对于这个正在做prefill的seq，确定它在下一次迭代中要送去做prefill的tokens数量。
        # 这个数量 = min(该序列还没有做prefill的tokens数，batch中可用的prefill tokens配额)
        # =================================================================
        next_num_tokens = min(
            seq.get_prompt_len() - seq.get_num_prompt_tokens_processed(),
            chunk_size - num_batched_tokens,
        )

        return next_num_tokens

    def _schedule(self) -> SchedulerOutputs:
        # Fix the current time.
        now = time.monotonic()

        running: List[Sequence] = [] # 应该是用来存放确定要被本轮调度的数据
        ignored_seq_ids: List[str] = []
        preempted_seq_ids: List[str] = []
        scheduled_seq_metadata_list: List[SequenceScheduleMetadata] = []

        num_batched_tokens: int = 0

        ######################################################################
        # Phase 1: Add existing running sequence groups to the batch.
        # There are two cases:
        # 1. The sequence group has incomplete prefill. The routine
        # remains identical to the one in sarathi scheduler for such sequences.
        # 2. The sequence group has completed prefill. In this case, we need to
        # check for memory availability for the next chunk of decode tokens, and preempt
        # some sequence groups if necessary. Note that, the preempted sequence groups
        # might belong to either of the two categories.
        ######################################################################

        # NOTE(woosuk): Preemption happens only when there is no available slot
        # to keep all the sequence groups in the RUNNING state.
        # In this case, the policy is responsible for deciding which sequence
        # groups to preempt.
        
        # =================================================================
        # 把self.running中的数据按照FCFS原则（先来后到）进行排序
        # =================================================================
        self.running = self.policy.sort_by_priority(now, self.running)

        # in first pass process all the requests with prefill completed
        # this allows us to accurately account for the number of decode tokens
        running_prefills: List[Sequence] = []

        # =================================================================
        # 先去看上一次iteration中被选中的序列
        # =================================================================
        while self.running:
            seq = self.running.pop(0)
            # =================================================================
            # 如果这个seq没有被暂停，那么就把它继续添加到本轮running队列中
            # 
            # （上一轮调度结束后，所有running状态的序列都会被设置为pause状态，
            # 这里可以参考base_sequence_manager的on_step_completed函数，
            # 这个函数是对每轮调度结束后序列的状态和推理结果做处理），
            # 
            # （当然也可能有别的条件会触发pause状态设置，这里没有看完全部源码，所以暂不知道）
            # =================================================================
            if not seq.is_paused():
                running.append(seq)
                continue

            # =================================================================
            # 如果这个seq还没有做完prefill，就把它添加到running_prefill的列表中
            # =================================================================
            if not seq.prompt_processing_finished:
                running_prefills.append(seq)
                continue

            # =================================================================
            # （走到这一步，剩下的都是上一次调度中处于decode阶段的seq了）
            # 如果现在没有足够的空间给处于decode阶段的seq做推理了
            # =================================================================
            while not self.block_manager.can_append_slot():
                # =================================================================
                # 如果self.running队列中有数据，就从running队列中抢占最晚到来的那个
                # sarathi中的抢占是直接做重计算，即把seq重新放回waiting队列中
                # =================================================================
                if self.running:
                    # Preempt the lowest-priority sequence groups.
                    victim_seq = self.running.pop(-1)
                    self._preempt(victim_seq)
                    preempted_seq_ids.append(victim_seq.seq_id)
                # =================================================================
                # 如果self.running队列中已经没有数据了，就抢占当前seq
                # =================================================================
                else:
                    # No other sequence groups can be preempted.
                    # Preempt the current sequence group.
                    self._preempt(seq)
                    preempted_seq_ids.append(seq.seq_id)
                    break
            # =================================================================
            # 如果现在有足够空间给处于decode阶段的seq做推理
            # =================================================================
            else:
                # 给decode阶段的seq分配KV cache空间，并将其添加到本轮的running队列中
                self._append_slot(seq)
                running.append(seq)
                # 当前batch的token数量 += 1
                num_batched_tokens += 1
                scheduled_seq_metadata_list.append(
                    SequenceScheduleMetadata.from_sequence(seq)
                )
        
        # =================================================================
        # 接下来处理上一次调度中没有做完prefill的seq
        # 他们的KV cache空间肯定是够的，因为对于一个seq，我们在一开始是根据
        # 它完整的prefill序列长度来分配KV cache，而不是根据prefill chunk大小分配
        # KV cache。所以无论是那一轮iteration，我们都给这个seq的prefill留足了
        # KV cache空间
        # now add the requests with prefill incomplete
        # the memory for all these prefills has already been allocated
        # so we should be able to run all of them
        # =================================================================
        for seq in running_prefills:
            assert not seq.prompt_processing_finished
            # =================================================================
            # 计算对于这个seq，这次调度可以放多少tokens去做prefill
            # =================================================================
            next_num_prefill_tokens = self._get_seq_next_num_prefill_tokens(
                seq, num_batched_tokens
            )

            # as long as the request could fit in the batch previously
            # it should be able to fit in the batch now
            # so in non-pipeline case this condition should always be false
            # however, in pipeline case, the grouping of requests can change
            # between different microbatches, so this is not guaranteed to be always true
            if next_num_prefill_tokens == 0:
                running.append(seq)
                continue

            num_batched_tokens += next_num_prefill_tokens
            scheduled_seq_metadata_list.append(
                SequenceScheduleMetadata.from_sequence(
                    seq, prompt_chunk_len=next_num_prefill_tokens
                )
            )
            running.append(seq)

        ######################################################################
        # Phase 2: Add waiting (new) sequence groups to the batch.
        # This routine is nearly-identical to the one in sarathi scheduler
        # 在phase1中，我们遍历了上一个iteration的batch，来决定有哪些seq可以继续做
        # 这一轮的推理。
        # 在phase2中，我们去waiting队列中继续搜寻，看看是否有新请求能加入这一轮推理
        # 也就是每次调度中，batch = 上一轮batch筛选后的结果 + waiting队列中筛选的结果
        ######################################################################
        # Optimization: We do not sort the waiting queue since the preempted
        # sequence groups are added to the front and the new sequence groups
        # are added to the back.
        while self.waiting:
            seq = self.waiting[0]

            # This is required to handle benchmarking where we set request arrival time ahead of time
            if seq.arrival_time > now:
                break

            if not self._check_request_prompt_length(seq):
                ignored_seq_ids.append(seq.seq_id)
                continue

            # =================================================================
            # If the sequence group cannot be allocated, stop.
            # 直接用了vllm的allocate方法，即不是根据seq的prefill chunk大小
            # 预分配物理块的，而是直接根据整个seq的prefill大小分配物理块的
            # =================================================================
            if not self.block_manager.can_allocate(seq):
                # this is different from vllm scheduler
                # even if we cannot allocate this sequence group
                # there might be other sequence groups that can be allocated
                break

            # The total number of sequences in the RUNNING state should not
            # exceed the maximum number of sequences.
            if len(running) >= self.scheduler_config.max_num_seqs:
                break

            # check if we can fit the prefill in the batch
            next_num_prefill_tokens = self._get_seq_next_num_prefill_tokens(
                seq, num_batched_tokens
            )

            if next_num_prefill_tokens == 0:
                break

            seq = self.waiting.pop(0)
            self._allocate(seq) # 直接为完整的seq prefill（而不是chunk prefill）分配KV cache空间
            num_batched_tokens += next_num_prefill_tokens
            scheduled_seq_metadata_list.append(
                SequenceScheduleMetadata.from_sequence(
                    seq, prompt_chunk_len=next_num_prefill_tokens
                )
            )
            running.append(seq)

        # make sure that prefills are at the start of the batch, so that we don't violate assumptions
        # made in the original vllm codebase
        self.running = running

        return SchedulerOutputs(
            id=self._iteration_id,
            ignored_seq_ids=ignored_seq_ids,
            preempted_seq_ids=preempted_seq_ids,
            scheduled_seq_metadata_list=scheduled_seq_metadata_list,
        )