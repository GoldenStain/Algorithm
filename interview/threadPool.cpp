#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <functional>
#include <utility>
#include <atomic>

template <typename T> class BlockQueue {
public:
  BlockQueue(bool non_block = false) : non_block(non_block) {}
  ~BlockQueue() {
    // set non_block
    {
        std::lock_guard<std::mutex> lock(producer_mutex);
        non_block = true;
        not_empty.notify_all();
    }
    // clear producer_queue
    {
        std::lock_guard<std::mutex> lock(producer_mutex);
        while (!producer_queue.empty()) {
            producer_queue.pop();
        }
    }
    // clear consumer_queue
    {
        std::lock_guard<std::mutex> lock(consumer_mutex);
        while (!consumer_queue.empty()) {
            consumer_queue.pop();
        }
    }
  }

  void Push(const T &value) {
    std::lock_guard<std::mutex> lock(producer_mutex);
    producer_queue.push(value);
    not_empty.notify_one();
  }

  bool Pop(T &value) {
    std::unique_lock<std::mutex> lock(consumer_mutex);
    if (consumer_queue.empty() && SwapQueue() == 0)
      return false;
    value = consumer_queue.front();
    consumer_queue.pop();
    return true;
  }

  void Cancle() {
    std::lock_guard<std::mutex> lock(producer_mutex);
    non_block = true;
    not_empty.notify_all();
  }

private:
  bool non_block;
  std::queue<T> producer_queue, consumer_queue;
  std::mutex producer_mutex, consumer_mutex;
  std::condition_variable not_empty;

  int SwapQueue() {
    // Swap producer_queue and consumer_queue when consumer_queue is empty
    std::unique_lock<std::mutex> lock(producer_mutex);
    not_empty.wait(lock,
                   [this] { return non_block || !producer_queue.empty(); });
    std::swap(producer_queue, consumer_queue);
    return consumer_queue.size();
  }
};

class ThreadPool {
public:
  explicit ThreadPool(int num_threads) {
    for (int i = 0; i < num_threads; i++) {
        workers.emplace_back([this] {Worker();});
    }
  }

  ~ThreadPool() {
    task_queue.Cancle();
    for (auto &worker: workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
  }

  template<typename F, typename... Args>
  void Post(F &&f, Args&&... args) {
    auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    task_queue.Push(task);
  }
private:
  BlockQueue<std::function<void()>> task_queue;
  std::vector<std::thread> workers;
  void Worker() {
    while (true) {
        std::function<void()> task;
        if (!task_queue.Pop(task)) {
            break;
        }
        task();
    }
  }
};

std::atomic<int> task_counter{0};

void Task(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Task " << id << " executed by " << std::this_thread::get_id() << std::endl;
    int old_counter = task_counter.load(std::memory_order_relaxed);
    task_counter.store(old_counter + 1);
}

void Producer(ThreadPool& pool, int proudcer_id, int num_tasks) {
    for (int i = 0; i < num_tasks; i++) {
        int task_id = proudcer_id * 100 + num_tasks;
        pool.Post(Task, task_id);
        std::cout << "Producer " << proudcer_id << " posted task " << task_id << std::endl; 
    }
}

int main() { 
    const int num_producers = 4, num_tasks_per_producer = 10, num_threads_in_pool = 2;
    ThreadPool pool(8);
    std::vector<std::thread> producers;
    for (int i = 0; i < num_producers; i++) {
        producers.emplace_back(Producer, std::ref(pool), i, num_tasks_per_producer);
    }
    for (auto &pi : producers) {
        pi.join();
    }
    while(task_counter.load() < num_tasks_per_producer * num_producers) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "All tasks completed. Total tasks executed: " << task_counter << std::endl;

    return 0; }