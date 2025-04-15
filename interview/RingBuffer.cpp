#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <type_traits>

template <typename T, size_t Capacity> class RingBuffer {
public:
  static_assert(Capacity && !(Capacity & (Capacity - 1)),
                "Capacity must be power of 2!\n");
  RingBuffer() : read_(0), write_(0) {}
  ~RingBuffer() {
    size_t r = read_.load(std::memory_order_relaxed),
           w = write_.load(std::memory_order_relaxed);
    size_t remaining = (w - r + Capacity) & (Capacity - 1);
    while (remaining--) {
      reinterpret_cast<T *>(&data_[r])->~T();
      r = (r + 1) & (Capacity - 1);
    }
  }
  template <typename U>
  // 如果直接用T，T会被推导为具体类型（应该还会有引用折叠），无法触发完美转发
  bool Push(U &&value) noexcept {
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
  template <typename U> bool Push_over_write(U &&value) noexcept {
    const size_t w = write_.load(std::memory_order_relaxed);
    const size_t next_w = (w + 1) & (Capacity - 1);

    // Check if the buffer is full
    if (next_w == read_.load(std::memory_order_acquire)) {
      read_.store((read_.load(std::memory_order_relaxed) + 1) & (Capacity - 1),
                  std::memory_order_relaxed);
    }

    // put new element
    new (&data_[w]) T(std::forward<U>(value));
    write_.store(next_w, std::memory_order_release);
    return true;
  }

  bool Pop(T &val) noexcept {
    const size_t r = read_.load(std::memory_order_relaxed);

    // Check
    if (r == write_.load(std::memory_order_acquire)) {
      return false;
    }

    val = std::move(*reinterpret_cast<T *>(&data_[r]));
    reinterpret_cast<T *>(&data_[r])->~T();

    // update
    read_.store((r + 1) & (Capacity - 1), std::memory_order_release);
    return true;
  }

  size_t Size() const noexcept {
    size_t r = read_.load(std::memory_order_relaxed),
           w = write_.load(std::memory_order_relaxed);
    // 因为是循环队列，所以要加上Capacity
    return (w - r + Capacity) & (Capacity - 1);
  }

private:
  // cache align, read_和write_就是头尾指针
  alignas(64) std::atomic<size_t> read_;  // head
  alignas(64) std::atomic<size_t> write_; // tail
  // 注意这里不是一个函数，是一个类型别名，所以要用[]，而不是()
  // 用法：<大小，对齐方式>
  alignas(64) std::aligned_storage_t<sizeof(T), alignof(T)> data_[Capacity];
};

void producer(RingBuffer<int, 8>& buffer) {
    for (int i = 0; i < 20; i++) {
        while(!buffer.Push(i)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        std::cout << "Produced: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void consumer(RingBuffer<int, 8>& buffer) {
    for (int i = 0; i < 20; i++) {
        int value;
        while (!buffer.Pop(value)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::cout << "Consumed: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    RingBuffer<int, 8> buffer;

    std::thread p(producer, std::ref(buffer));
    std::thread c(consumer, std::ref(buffer));
    p.join();
    c.join();
    return 0;
}