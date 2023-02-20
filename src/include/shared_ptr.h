#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>

#define DEBUG

namespace STL {
template <typename T>
class shared_ptr {
 private:
  T *ptr_{nullptr};
  size_t *refcnt_{nullptr};

  void inc_() {
    if (refcnt_ != nullptr) {
      (*refcnt_)++;
    }
  }

  void dec_() {
    if (refcnt_ != nullptr) {
      (*refcnt_)--;
      if (*refcnt_ == 0) {
        delete ptr_;
        delete refcnt_;
      }
    }
  }

 public:
  // constructor
  explicit shared_ptr(T *ptr = nullptr) {
    if (ptr != nullptr) {
      refcnt_ = new size_t(1);
    }
    ptr_ = ptr;
  }

  shared_ptr(const shared_ptr<T> &other) {
    ptr_ = other.ptr_;
    refcnt_ = other.refcnt_;
    inc_();
  }

  shared_ptr(shared_ptr<T> &&other) noexcept {
    ptr_ = other.ptr_;
    refcnt_ = other.refcnt_;
    other.ptr_ = nullptr;
    other.refcnt_ = 0;
  }

  // destructor
  ~shared_ptr() { dec_(); }

  // assignment
  shared_ptr<T> &operator=(const shared_ptr<T> &other) {
    dec_();
    ptr_ = other.ptr_;
    refcnt_ = other.refcnt_;
    inc_();
  }

  constexpr shared_ptr<T> &operator=(shared_ptr<T> &&other) {
    ptr_ = other.ptr_;
    refcnt_ = other.refcnt_;
    other.ptr_ = nullptr;
    other.refcnt_ = 0;
  }

  // modifier
  void reset() {
    dec_();
    ptr_ = nullptr;
    refcnt_ = nullptr;
  }

  void reset(T *ptr) {
    dec_();
    ptr_ = ptr;
    refcnt_ = new size_t(1);
  };

  void swap(shared_ptr<T> &other) {
    auto temp_refcnt = refcnt_;
    auto temp_ptr = ptr_;
    refcnt_ = other.refcnt_;
    ptr_ = other.ptr_;
    other.refcnt_ = temp_refcnt;
    other.ptr_ = temp_ptr;
  }

  // observer
  T *get() const { return ptr_; }

  size_t use_count() const {
    if (refcnt_ != nullptr) {
      return *refcnt_;
    }
    return 0;
  }

  explicit operator bool() const { return get() != nullptr; }

  T &operator*() const {
    if (ptr_ != nullptr) {
      return *ptr_;
    }
    throw std::exception();
  }

  T *operator->() const {
    if (ptr_ != nullptr) {
      return ptr_;
    }
    throw std::exception();
  }

  // for debug
  void view() { std::cout << "shared_ptr<" << typeid(T *).name() << ">(" << use_count() << ")" << std::endl; }
};

}  // namespace STL
