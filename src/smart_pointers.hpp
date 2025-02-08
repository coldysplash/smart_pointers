#pragma once

namespace SmartPointers {

template <typename T> struct DefaultDeleter {
  void operator()(T *ptr) const { delete ptr; }
};

template <typename T, typename Deleter = DefaultDeleter<T>>
class uniquePtr : private Deleter {
private:
  T *ptr_ = nullptr;
  Deleter deleter_;

  Deleter &get_deleter() { return deleter_; }

public:
  uniquePtr() = default;

  explicit uniquePtr(T *ptr) : ptr_(ptr) {}

  uniquePtr(const uniquePtr &other) = delete;
  uniquePtr &operator=(const uniquePtr &other) = delete;

  uniquePtr(uniquePtr &&other) : ptr_(other.ptr_) { other.ptr_ = nullptr; }
  uniquePtr &operator=(uniquePtr &&other) {
    reset(other.release());
    return *this;
  }

  T &operator*() const { return *ptr_; }
  T *operator->() const { return ptr_; }

  T *get() const { return ptr_; }

  T *release() {
    T *old = ptr_;
    ptr_ = nullptr;
    return old;
  }

  void reset(T *ptr = nullptr) {
    get_deleter()(ptr_);
    ptr_ = ptr;
  }
};
} // namespace SmartPointers