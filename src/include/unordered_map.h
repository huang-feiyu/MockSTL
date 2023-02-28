#pragma once
#include <cmath>
#include <cstdlib>
#include <functional>
#include <memory>
#include <optional>
#include "list.h"
#include "shared_ptr.h"
#include "vector.h"

#define DEBUG

namespace STL {

template <typename Key, typename T, class Hash = std::hash<Key>>
class unordered_map {
 public:
  using kv_t = std::pair<const Key, T>;
  using const_iterator = typename list<kv_t>::const_iterator;
  using iterator = typename list<kv_t>::iterator;

 private:
  /* a table  => multiple buckets
   * a bucket => multiple kv pairs (might be duplicate keys)
   */
  vector<list<iterator>> buckets_;  // bucket with multiple iterator/location in
  list<kv_t> kvs_;                  // all elements (unordered)

  size_t size_{0};      // number of kv pairs; size of kvs_
  size_t capacity_{1};  // for hash modula;    size of buckets_

  Hash hash_func_{std::hash<Key>()};
  float max_load_factor_{1.5};  // determine the average max number of kv pairs within a bucket

  size_t hash_(const Key &key) { return hash_func_(key) % capacity_; }

  size_t hash_(const kv_t &elem) { return hash_func_(elem.first) % capacity_; }

  std::optional<iterator> get_(const Key &key) {
    auto i = hash_(key);
    for (auto itr = buckets_[i].begin(); itr != buckets_[i].end(); itr++) {
      if (itr.node_->val_->first == key) {
        return std::optional<iterator>(*itr);
      }
    }
    return std::optional<iterator>();
  }

  std::optional<iterator> get_(const kv_t &elem) { return get_(elem.first); }

  // insert or assign
  void insert_(const kv_t &elem, bool assign = false) {
    std::optional<iterator> opt = get_(elem);
    if (opt.has_value()) {
      if (assign) {
        opt.value().node_->val_.second = elem.second;
      }
      return;
    }

    // insert into kv list
    kvs_.push_back(elem);
    // insert into specific bucket
    auto itr = kvs_.end();
    itr--;
    auto i = hash_(elem);
    buckets_[i].push_back(itr);

    size_++;
    if (size_ > max_load_factor_ * capacity_) {
      rehash_(capacity_ * 2);
    }
  }

  void rehash_(size_t count) {
    buckets_.clear();
    buckets_.resize(count);
    capacity_ = count;
    for (auto itr = kvs_.begin(); itr != kvs_.end(); itr++) {
      insert_(*itr);
    }
  }

 public:
  // constructor
  explicit unordered_map(size_t capacity = 1) : capacity_(capacity) { buckets_.resize(capacity); }

  unordered_map(std::initializer_list<kv_t> init) {
    rehash_(std::ceil(init.size() / max_load_factor()));
    for (auto itr = init.begin(); itr != init.end(); itr++) {
      insert_(*itr);
    }
  }

  unordered_map(const unordered_map<Key, T, Hash> &other) {
    buckets_ = other.buckets_;
    kvs_ = other.kvs_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    hash_func_ = other.hash_func_;
    max_load_factor_ = other.max_load_factor_;
  }

  unordered_map(unordered_map<Key, T, Hash> &&other) noexcept {
    buckets_ = other.buckets_;
    kvs_ = other.kvs_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    hash_func_ = other.hash_func_;
    max_load_factor_ = other.max_load_factor_;

    other.clear();
  }

  // destructor
  ~unordered_map() { clear(); }

  // assignment
  unordered_map &operator=(const unordered_map &other) {
    buckets_ = other.buckets_;
    kvs_ = other.kvs_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    hash_func_ = other.hash_func_;
  }

  unordered_map &operator=(unordered_map &&other) noexcept {
    buckets_ = other.buckets_;
    kvs_ = other.kvs_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    hash_func_ = other.hash_func_;
    max_load_factor_ = other.max_load_factor_;

    other.clear();
  }

  // iterator
  iterator begin() { return iterator(kvs_.begin()); }
  iterator end() { return iterator(kvs_.end()); }
  const_iterator begin() const { return const_iterator(kvs_.begin()); }
  const_iterator end() const { return const_iterator(kvs_.end()); }

  // capacity
  bool empty() const noexcept { return size_ == 0; }
  size_t size() const noexcept { return size_; }

  // modifier
  /**
   * NOTE:
   * 1. ignore some details, it's too boring.
   * 2. some spec is different than cpp-reference, also boring.
   **/
  void clear() noexcept {
    buckets_.clear();
    kvs_.clear();
    size_ = 0;
  }

  void insert(const kv_t &value) { insert_(value); }

  void insert(kv_t &&value) { insert_(value); }

  void erase(iterator pos) {
    auto i = hash_(pos->first);
    for (auto itr = buckets_[i].begin(); itr != buckets_[i].end(); itr++) {
      if (itr.node_->val_->first == pos->first) {
        buckets_[i].erase(itr);
      }
    }
    kvs_.erase(pos);
    size_--;
  }

  void swap(unordered_map &other) {
    buckets_.swap(other.buckets_);
    kvs_.swap(other.kvs_);
    auto tmp_size = size_;
    size_ = other.size_;
    other.size_ = tmp_size;
    auto tmp_capacity = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = tmp_capacity;
    auto tmp_hash_func = hash_func_;
    hash_func_ = other.hash_func_;
    other.hash_func_ = tmp_hash_func;
    auto tmp_max_load_factor = max_load_factor_;
    max_load_factor_ = other.max_load_factor_;
    other.max_load_factor_ = tmp_max_load_factor;
  }

  // observer
  iterator find(const Key &key) {
    std::optional<iterator> opt = get_(key);
    if (opt.has_value()) {
      return opt.value();
    }
    return end();
  }

  T &at(const Key &key) {
    std::optional<iterator> opt = get_(key);
    if (opt.has_value()) {
      return opt.value().node_->val_.second;
    }
    throw std::exception();
  }

  T &operator[](const Key &key) {
    std::optional<iterator> opt = get_(key);
    if (opt.has_value()) {
      return opt.value().node_->val_.second;
    }
    insert_({key, T{}});
    return at(key);
  }

  size_t count(const Key &key) { return get_(key).has_value() ? 1 : 0; }

  // bucket API
  size_t bucket(const Key &key) const { return hash_(key); }
  size_t bucket_size(size_t n) const { return buckets_[n].size(); }
  size_t bucket_count() const { return capacity_; }

  // hash strategy
  float load_factor() const { return static_cast<float>(size_) / capacity_; }
  float max_load_factor() const { return max_load_factor_; }
  void max_load_factor(float ml) { max_load_factor_ = ml; }

  void rehash(size_t count) { rehash_(count); }

  void reserve(size_t count) { rehash(std::ceil(count / max_load_factor())); }

  std::hash<T> hash_function() const { return hash_func_; }

  // debug
  void view() {
#ifdef DEBUG
    std::cout << "unordered_map => sz(" << size_ << ") cap(" << capacity_ << ")" << std::endl;
    for (auto i = 0; i < capacity_; i++) {
      std::cout << "\tbucket[" << i << "] : [";
      if (!buckets_[i].empty()) {
        auto end = buckets_[i].end();
        end--;
        for (auto itr = buckets_[i].begin(); itr != end; itr++) {
          std::cout << "(" << itr->node_->val_.first << "," << itr->node_->val_.second << "), ";
        }
        std::cout << "(" << end->node_->val_.first << "," << end->node_->val_.second << ")";
      }
      std::cout << "]" << std::endl;
    }
    std::cout << std::endl;
#endif
  }
};

}  // namespace STL
