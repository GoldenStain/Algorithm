#include <algorithm>
#include <atomic>
#include <cstddef>
#include <iostream>

template <typename T> class MySharedPtr {
private:
  T *my_ptr = nullptr;
  std::atomic<unsigned int> *my_ref_count = nullptr;

public:
  MySharedPtr() : my_ptr(nullptr), my_ref_count(nullptr) {}

  MySharedPtr(T *input_)
      : my_ptr(input_), my_ref_count(new std::atomic<unsigned int>(1)) {}

  MySharedPtr(const MySharedPtr &other) {
    my_ptr = other.my_ptr;
    my_ref_count = other.my_ref_count;
    if (my_ref_count != nullptr) {
      (*my_ref_count)++;
    }
  }

  ~MySharedPtr() {
    if (my_ref_count == nullptr) {
      return;
    }
    if (--(*my_ref_count) > 0) {
      return;
    }
    if (my_ptr != nullptr) {
      delete my_ptr;
    }
    delete my_ref_count;
  }

  MySharedPtr &operator=(const MySharedPtr &other) {
    if (my_ptr == other.my_ptr) {
      return *this;
    }

    if (my_ref_count != nullptr) {
      (*my_ref_count)--;
      if (*my_ref_count == 0) {
        delete my_ptr;
        delete my_ref_count;
      }
    }

    my_ptr = other.my_ptr;
    my_ref_count = other.my_ref_count;

    if (my_ref_count != nullptr) {
      (*my_ref_count)++;
    }

    return *this;
  }

  void swap(MySharedPtr &other) {
    std::swap(my_ptr, other.my_ptr);
    std::swap(my_ref_count, other.my_ref_count);
  }

  MySharedPtr(MySharedPtr &&other) : my_ptr(nullptr), my_ref_count(nullptr) {
    // 交换之后，原来的other持有的就变成了nullptr
    // 当前对象就变成了有效对象
    other.swap(*this);
  }

  MySharedPtr &operator=(MySharedPtr &&other) {
    // 先创建一个临时对象，触发移动构造函数
    // 清空other
    // 退出作用域之后，临时对象也被清楚
    MySharedPtr(std::move(other)).swap(*this);
    return *this;
  }

  // 工具函数
  T *operator->() const { return my_ptr; }

  T &operator*() const { return *my_ptr; }

  T *get() const { return my_ptr; }

  unsigned int use_count() const {
    unsigned int res = my_ref_count->load(std::memory_order_acq_rel);
    return res;
  }
};