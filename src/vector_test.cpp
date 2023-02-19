#include "include/vector.h"
#include <gtest/gtest.h>

namespace STL {
TEST(VectorTests, TestConstructor) {
  // 1. default
  vector<int> vec1;
  vec1.view();
  ASSERT_TRUE(vec1.empty() && vec1.capacity() == 0);

  // 2. arr with size
  auto arr2 = new int[5];
  for (auto i = 0; i < 5; i++) {
    arr2[i] = i;
  }
  auto vec2 = vector(arr2, 5);
  vec2.view();
  ASSERT_TRUE(vec2.size() == 5 && vec2.capacity() == 10);

  // 3. iterators
  auto arr3 = new int[5];
  for (auto i = 0; i < 5; i++) {
    arr3[i] = i;
  }
  auto vec3 = vector(arr3, arr3 + 5);
  vec3.view();
  ASSERT_TRUE(vec3.size() == 5 && vec3.capacity() == 10);

  // 4. only size
  auto vec4 = vector<int>(5);
  vec4.view();
  ASSERT_TRUE(vec4.empty() && vec4.capacity() == 5);

  // 5. size with initial value
  auto vec5 = vector<int>(5, 5);
  vec5.view();
  ASSERT_TRUE(vec5.size() == 5 && vec5.capacity() == 10);

  // 6. move constructor
  auto vec6 = vector<int>(std::move(vec5));
  vec6.view();
  ASSERT_TRUE(vec6.size() == 5 && vec6.capacity() == 10 && /* make sure vec5 is moved */ vec5.data() == nullptr);

  // 7. copy constructor
  auto vec7 = vector<int>(vec6);
  vec7.view();
  ASSERT_TRUE(vec7.size() == 5 && vec7.capacity() == 10 && vec6.data() != nullptr);

  // 8. initializer list
  auto vec8 = vector<int>({1, 2, 3, 4, 5});
  vec8.view();
  ASSERT_TRUE(vec8.size() == 5 && vec8.capacity() == 10);
}

}  // namespace STL
