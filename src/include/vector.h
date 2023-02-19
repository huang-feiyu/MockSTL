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
  void resize();

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
  void push_back(T elem);
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
  constexpr void operator=(const vector<T> &other);
  constexpr void operator=(vector<T> &&other) noexcept;
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
void vector<T>::resize() {
  /* if v.elements_num == capacity, new capacity = 2 * capacity ; */
  if (size() == capacity()) {
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
  resize();  // reverse space
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
    resize();
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
  resize();
}

template <typename T>
vector<T>::vector(vector<T> &&other) noexcept {
  // move to current
  arr_ = other.arr_;
  capacity_ = other.capacity();
  size_ = other.size();
  resize();
  other.arr_ = nullptr;
}

template <typename T>
vector<T>::vector(const vector<T> &other) {
  // copy to current
  arr_ = new T[other.size()];
  capacity_ = other.capacity();
  size_ = other.size();
  resize();
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

}  // namespace STL
