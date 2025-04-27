#include <algorithm>
#include <iostream>

template <typename T>
class MySharedPtr {
private:
  T *my_ptr = nullptr;
  unsigned int *my_ref_count = nullptr;
public:
  MySharedPtr(): my_ptr(nullptr), my_ref_count(nullptr) {}
  MySharedPtr(T* input_): my_ptr(input_), my_ref_count(new unsigned int(1)) {}
  MySharedPtr (const MySharedPtr &other) {
    
  }
};