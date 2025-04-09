#include <atomic>
#include <iostream>
#include <type_traits>

template <typename T, size_t Capacity> class RingBuffer {
public:
  static_assert(Capacity && !(Capacity & (Capacity - 1)),
                "Capacity must be power of 2!\n");
  RingBuffer() : read_(0), write_(0) {}
  template<typename U>
  // 如果直接用T，T会被推导为具体类型，无法触发完美转发
  bool Push(U&& value) noexcept {}

  bool Pop(T& val) noexcept {}

  size_t Size() const noexcept{}

private:
  // cache align
  alignas(64) std::atomic<size_t> read_;
  alignas(64) std::atomic<size_t> write_;
  // 注意这里不是一个函数，是一个类型别名，所以要用[]，而不是()
  // 用法：<大小，对齐方式>
  alignas(64) std::aligned_storage_t<sizeof(T), alignof(T)> data_[Capacity];
};