#pragma once
#include <cstring>
#include <iostream>

namespace STL {

class string {
 public:
  // normal constructor
  explicit string(const char *chars = nullptr) {
    if (chars == nullptr) {
      chars_ = new char[1];
      chars_[0] = '\0';
    } else {
      chars_ = new char[strlen(chars) + 1];
      strcpy(chars_, chars);
    }
  }

  // copy constructor
  string(const string &str) {
    chars_ = new char[strlen(str.chars_) + 1];
    strcpy(chars_, str.chars_);
  }

  // move constructor
  string(string &&str) noexcept {
    chars_ = str.chars_;
    str.chars_ = nullptr;
  }

  // destructor
  ~string() { delete[] chars_; }

  // chars assign
  string &operator=(const char *chars) {
    delete[] chars_;
    chars_ = new char[strlen(chars) + 1];
    strcpy(chars_, chars);
  }

  // copy assign
  string &operator=(const string &other) {
    if (this == &other) {
      return *this;
    }
    delete[] chars_;
    chars_ = new char[strlen(other.chars_) + 1];
    strcpy(chars_, other.chars_);
  }

  // move assign
  string &operator=(string &&other) noexcept {
    if (this == &other) {
      return *this;
    }
    delete[] chars_;
    chars_ = other.chars_;
    other.chars_ = nullptr;
  }

  // operator ==
  friend bool operator==(const string &str1, const string &str2) { return strcmp(str1.chars_, str2.chars_) == 0; }

  size_t size() const { return strlen(chars_); }

  const char *c_str() const { return chars_; }

  void view() { std::cout << "string[" << strlen(chars_) << "] => (" << chars_ << ")" << std::endl; }

  int hash() {
    int h = 0;
    for (size_t i = 0; i < strlen(chars_); ++i) {
      h = h * 31 + static_cast<int>(chars_[i]);
    }
    return h;
  }

 private:
  char *chars_{};
};
}  // namespace STL
