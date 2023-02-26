#pragma once

namespace STL {
class singleton {
 public:
  static singleton &getInstance() {
    static singleton instance;  // Guaranteed to be destroyed.
                                // Instantiated on first use.
    return instance;
  }

 private:
  singleton() = default;
  singleton(const singleton &) = delete;
  void operator=(const singleton &) = delete;
};
}  // namespace STL
