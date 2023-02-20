#pragma once
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#define DEBUG

namespace STL {
template <typename T>
class vector {
 private:
  T *arr_{nullptr};     // the dynamic array
  size_t size_{0};      // size of used memory/sizeof(T)
  size_t capacity_{0};  // size of occupied memory/sizeof(T)

  /* dynamic expansion */
  void resize_(bool force = false);

 public:
  using iterator = T *;              // random iterator
  using const_iterator = const T *;  // constant iterator

 public:
  // constructors
  vector();
  vector(T *arr, size_t size);
  vector(T *first, T *last);
  explicit vector(size_t size);
  vector(size_t size, const T &value);
  vector(vector<T> &&other) noexcept;
  vector(const vector<T> &other);
  vector(std::initializer_list<T> init);

  // destructor
  ~vector();

  // iterator
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // modifier
  void push_back(const T &value);
  void pop_back();
  void clear();

  void erase(iterator pos);
  void erase(vector<T>::iterator first, vector<T>::iterator last);

  void insert(vector<T>::iterator pos, const T &value);
  void insert(vector<T>::iterator pos, size_t size, const T &value);
  void insert(vector<T>::iterator pos, vector<T>::iterator first, vector<T>::iterator last);

  void resize(size_t size);
  void resize(size_t size, T value);

  void swap(vector<T> &other);

  // capacity
  bool empty() const noexcept;
  size_t max_size() const noexcept;
  size_t size() const noexcept;
  size_t capacity() const noexcept;
  T *data();
  void reserve(size_t new_cap);

  // operator
  T &operator[](size_t pos);
  const T &operator[](size_t pos) const;
  constexpr vector<T> &operator=(const vector<T> &other);
  constexpr vector<T> &operator=(vector<T> &&other) noexcept;
  bool operator==(const vector<T> &other);
  bool operator!=(const vector<T> &other);

  // debug helper
  void view() {
#ifdef DEBUG
    std::cout << "vector => sz(" << size_ << ") cap(" << capacity_ << ") : [";
    if (size_ > 0) {
      for (size_t i = 0; i < size_ - 1; i++) {
        std::cout << arr_[i] << ",";
      }
      std::cout << arr_[size_ - 1];
    }

    std::cout << "]" << std::endl;
#endif
  };
};

template <typename T>
void vector<T>::resize_(bool force) {
  /* if v.elements_num == capacity, new capacity = 2 * capacity ; */
  if (capacity_ == 0) {
    capacity_ = 1;
    arr_ = new int[1];
    return;
  }
  if (force || size() == capacity()) {
    auto new_arr = new T[capacity() * 2];
    memcpy(new_arr, arr_, capacity_ * sizeof(T));
    delete[] arr_;
    arr_ = new_arr;
    capacity_ = capacity() * 2;
  }
}

template <typename T>
vector<T>::vector() : size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(T *arr, size_t size) : arr_(arr), size_(size), capacity_(size) {
  resize_();  // reverse space
}
template <typename T>
vector<T>::vector(T *first, T *last) {
  // [first, last)
  if (last > first) {
    auto size = last - first;
    arr_ = new T[size];
    size_ = size;
    capacity_ = size;
    memcpy(arr_, first, size * sizeof(T));
    resize_();
  } else {
    throw std::exception();
  }
}

template <typename T>
vector<T>::vector(size_t size) : arr_(new T[size]), size_(0), capacity_(size) {}

template <typename T>
vector<T>::vector(size_t size, const T &value) : arr_(new T[size]), size_(size), capacity_(size) {
  for (size_t i = 0; i < size; i++) {
    arr_[i] = value;
  }
  resize_();
}

template <typename T>
vector<T>::vector(vector<T> &&other) noexcept {
  // move to current
  arr_ = other.arr_;
  capacity_ = other.capacity();
  size_ = other.size();
  resize_();
  other.arr_ = nullptr;
}

template <typename T>
vector<T>::vector(const vector<T> &other) {
  // copy to current
  arr_ = new T[other.size()];
  capacity_ = other.capacity();
  size_ = other.size();
  resize_();
  memcpy(arr_, other.arr_, other.size_ * sizeof(T));
}

template <typename T>
vector<T>::vector(std::initializer_list<T> init) {
  arr_ = new T[init.size() * 2];
  size_ = init.size();
  capacity_ = init.size() * 2;
  auto i = 0;
  for (auto itr = init.begin(); itr != init.end(); itr++) {
    arr_[i++] = *itr;
  }
}
template <typename T>
vector<T>::~vector() {
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
bool vector<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
size_t vector<T>::size() const noexcept {
  return size_;
}

template <typename T>
size_t vector<T>::capacity() const noexcept {
  return capacity_;
}

template <typename T>
size_t vector<T>::max_size() const noexcept {
  return capacity_ - size_;
}

template <typename T>
T *vector<T>::data() {
  return arr_;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return arr_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return arr_ + size_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return arr_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return arr_ + size_;
}

template <typename T>
void vector<T>::push_back(const T &value) {
  resize_();
  arr_[size_++] = value;
  resize_();
}

template <typename T>
void vector<T>::pop_back() {
  size_--;
}

template <typename T>
void vector<T>::clear() {
  size_ = 0;
}

template <typename T>
void vector<T>::erase(vector::iterator pos) {
  for (auto itr = begin(); itr != end(); itr++) {
    if (pos == itr) {
      memmove(pos, pos + 1, (end() - itr) * sizeof(T));
      size_--;
      break;
    }
  }
}

template <typename T>
void vector<T>::erase(vector::iterator first, vector::iterator last) {
  for (auto itr = begin(); itr != end(); itr++) {
    if (first == itr) {
      if (last > end()) {
        last = end();
      }
      memmove(first, last, (end() - itr) * sizeof(T));
      size_ -= (last - first);
      break;
    }
  }
}

template <typename T>
void vector<T>::insert(vector::iterator pos, const T &value) {
  if (pos < begin() || pos > end()) {
    throw std::exception();
  }
  auto idx = pos - begin();
  while (max_size() < 1) {
    resize_(true);
  }
  auto size_to_move = size_ - idx;
  memmove(arr_ + idx + 1, arr_ + idx, size_to_move * sizeof(T));
  arr_[idx] = value;
  size_++;
}

template <typename T>
void vector<T>::insert(vector::iterator pos, size_t size, const T &value) {
  if (pos < begin() || pos > end()) {
    throw std::exception();
  }
  auto idx = pos - begin();
  while (max_size() < size) {
    resize_(true);
  }
  auto size_to_move = size_ - idx;
  memmove(arr_ + idx + size, arr_ + idx, size_to_move * sizeof(T));
  for (auto i = 0; i < size; i++) {
    arr_[idx + i] = value;
  }
  size_ += size;
}

template <typename T>
void vector<T>::insert(vector::iterator pos, vector::iterator first, vector::iterator last) {
  if (pos < begin() || pos > end() || last <= first) {
    throw std::exception();
  }
  auto idx = pos - begin();
  auto size = last - first;
  while (max_size() < size) {
    resize_(true);
  }
  auto size_to_move = size_ - idx;
  memmove(arr_ + idx + size, arr_ + idx, size_to_move * sizeof(T));
  auto i = 0;
  for (auto itr = first; itr != last; itr++) {
    arr_[idx + i++] = *itr;
  }
  size_ += size;
}

template <typename T>
void vector<T>::resize(size_t size) {
  while (capacity() < size) {
    resize_(true);
  }
  size_ = size;
  for (auto i = size_; i < capacity_; i++) {
    arr_[i] = 0;
  }
}

template <typename T>
void vector<T>::resize(size_t size, T value) {
  auto old_size = size_;
  while (capacity() < size) {
    resize_(true);
  }
  size_ = size;
  for (auto i = old_size; i < size_; i++) {
    arr_[i] = value;
  }
}

template <typename T>
void vector<T>::swap(vector<T> &other) {
  auto tmp_size = size_;
  auto tmp_arr = arr_;
  auto tmp_capacity = capacity_;
  size_ = other.size_;
  arr_ = other.arr_;
  capacity_ = other.capacity_;
  other.size_ = tmp_size;
  other.arr_ = tmp_arr;
  other.capacity_ = tmp_capacity;
}

template <typename T>
void vector<T>::reserve(size_t new_cap) {
  while (capacity() < new_cap) {
    resize_(true);
  }
}

template <typename T>
T &vector<T>::operator[](size_t pos) {
  return arr_[pos];
}

template <typename T>
const T &vector<T>::operator[](size_t pos) const {
  return arr_[pos];
}

template <typename T>
constexpr vector<T> &vector<T>::operator=(const vector<T> &other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  delete[] arr_;
  arr_ = new T[capacity_];
  memmove(arr_, other.arr_, capacity_ * sizeof(T));
}

template <typename T>
constexpr vector<T> &vector<T>::operator=(vector<T> &&other) noexcept {
  size_ = other.size_;
  capacity_ = other.capacity_;
  delete[] arr_;
  arr_ = other.arr_;

  other.arr_ = nullptr;
}

template <typename T>
bool vector<T>::operator==(const vector<T> &other) {
  if (size_ != other.size_) {
    return false;
  }
  for (auto i = 0; i < size_; i++) {
    if ((*this)[i] != other[i]) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool vector<T>::operator!=(const vector<T> &other) {
  return !(*this == other);
}

}  // namespace STL
