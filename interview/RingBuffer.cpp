#include <atomic>
#include <iostream>
#include <type_traits>

template <typename T, size_t Capacity> class RingBuffer {
public:
  static_assert(Capacity && !(Capacity & (Capacity - 1)),
                "Capacity must be power of 2!\n");
  RingBuffer() : read_(0), write_(0) {}
  template<typename U>
  // 如果直接用T，T会被推导为具体类型（应该还会有引用折叠），无法触发完美转发
  bool Push(U&& value) noexcept {
    const size_t w = write_.load(std::memory_order_relaxed);
    const size_t next_w = (w + 1) & (Capacity - 1);

    // Check if the buffer is full
    if (next_w == read_.load(std::memory_order_acquire))
        return false;

    // put new element
    new (&data_[w]) T(std::forward<U>(value));
    write_.store(next_w, std::memory_order_release);
    return true;
  }

  bool Pop(T& val) noexcept {}

  size_t Size() const noexcept{}

private:
  // cache align, read_和write_就是头尾指针
  alignas(64) std::atomic<size_t> read_; // head
  alignas(64) std::atomic<size_t> write_;// tail
  // 注意这里不是一个函数，是一个类型别名，所以要用[]，而不是()
  // 用法：<大小，对齐方式>
  alignas(64) std::aligned_storage_t<sizeof(T), alignof(T)> data_[Capacity];
};