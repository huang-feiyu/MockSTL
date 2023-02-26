#pragma once
#include "shared_ptr.h"

#define DEBUG

namespace STL {

template <typename T>
class list {
 public:
  struct node {
    T val_{};
    node *prev_{nullptr};
    node *next_{nullptr};

    explicit node() = default;

    explicit node(T val) : val_(val) {}

    node(const node &other) {
      val_ = other.val_;
      prev_ = other.prev_;
      next_ = other.next_;
    }
  };

  class Iterator {
   public:
    node *node_{nullptr};

   public:
    Iterator() = delete;
    explicit Iterator(node &node) : node_(&node){};
    explicit Iterator(node *node) : node_(node){};
    ~Iterator() = default;

    T &operator*() { return node_->val_; }
    T *operator->() { return &(node_->val_); }
    // ++itr
    Iterator operator++() {
      node_ = node_->next_;
      return *this;
    };

    // itr++
    Iterator operator++(int) {
      auto old = node_;
      operator++();
      return Iterator(old);
    };

    // --itr
    Iterator operator--() {
      node_ = node_->prev_;
      return *this;
    }
    // itr--
    Iterator operator--(int) {
      auto old = node_;
      operator--();
      return Iterator(old);
    }

    bool operator==(Iterator other) { return node_ == other.node_; }
    bool operator!=(Iterator other) { return node_ != other.node_; }

    void operator=(const Iterator &other) { node_ = other.node_; }
  };

  using iterator = Iterator;
  using const_iterator = const Iterator;

 private:
  // double list with dummy tail and head
  node *head_{};
  node *tail_{};
  size_t size_{0};

  void init_() {
    head_ = new node();
    tail_ = new node();
    head_->next_ = tail_;
    head_->prev_ = tail_;
    tail_->next_ = head_;
    tail_->prev_ = head_;
  }

  void insert_(const T &val, node *next) {
    auto node = new struct node(val);
    auto prev = next->prev_;
    node->next_ = next;
    node->prev_ = prev;
    prev->next_ = node;
    next->prev_ = node;
    size_++;
  }

  void remove_(node *node) {
    auto prev = node->prev_;
    auto next = node->next_;

    prev->next_ = next;
    next->prev_ = prev;
    delete node;
    size_--;
  }

 public:
  // constructor
  list() { init_(); }

  list(std::initializer_list<T> init) {
    init_();
    for (auto itr = init.begin(); itr != init.end(); itr++) {
      insert_(*itr, tail_);
    }
  }

  list(const list<T> &other) {
    init_();
    for (auto itr = other.begin(); itr != other.end(); itr++) {
      insert_(*itr, tail_);
    }
  }

  list(list<T> &&other) noexcept {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    other.init_();
  }

  // destructor
  ~list() {
    for (auto curr = head_; curr != tail_; curr = curr->next_) {
      delete curr;
    }
    delete tail_;
  }

  // iterator
  iterator begin() { return Iterator(head_->next_); }
  iterator end() { return Iterator(tail_); }
  const_iterator begin() const { return Iterator(head_->next_); }
  const_iterator end() const { return Iterator(tail_); }

  // capacity
  bool empty() { return size_ == 0; }
  size_t size() const { return size_; }

  // modifier
  void push_back(const T &value) { insert_(value, tail_); }

  void pop_back() {
    if (size_ == 0) {
      throw std::exception();
    }
    remove_(tail_->prev_);
  }

  void push_front(const T &value) { insert_(value, head_->next_); }

  void pop_front() {
    if (size_ == 0) {
      throw std::exception();
    }
    remove_(head_->next_);
  }

  void clear() {
    for (node *curr = head_->next_; curr != tail_; curr = curr->next_) {
      remove_(curr);
    }
  }

  void erase(iterator pos) { remove_(pos.node_); }

  void insert(iterator pos, const T &value) { insert_(value, pos.node_); }

  void swap(list &other) {
    auto tmp_size = size_;
    auto tmp_head = head_;
    auto tmp_tail = tail_;

    size_ = other.size_;
    head_ = other.head_;
    tail_ = other.tail_;

    other.size_ = tmp_size;
    other.head_ = tmp_head;
    other.tail_ = tmp_tail;
  }

  // operator
  bool operator==(const list<T> &other) {
    if (size() != other.size()) {
      return false;
    }
    auto itr1 = begin();
    auto itr2 = other.begin();
    for (; itr1 != end(); itr1++, itr2++) {
      if (*itr1 != *itr2) {
        return false;
      }
    }
    return true;
  }

  void view() {
#ifdef DEBUG
    std::cout << "list => sz(" << size_ << ") : [";
    if (size_ > 0) {
      auto end = this->end();
      end--;
      for (auto itr = begin(); itr != end; itr++) {
        std::cout << *itr << ",";
      }
      std::cout << *end;
    }
    std::cout << "]" << std::endl;
#endif
  }
};

}  // namespace STL
