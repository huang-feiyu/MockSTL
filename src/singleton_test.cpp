#include "include/singleton.h"
#include <gtest/gtest.h>

namespace STL {

TEST(SingletonTests, TestSingleton) {
  singleton single{};
  ASSERT_TRUE(&(single.getInstance()) == &(singleton::getInstance()));

  singleton single2{};
  ASSERT_TRUE(&(single2.getInstance()) == &(singleton::getInstance()));
}

}  // namespace STL
