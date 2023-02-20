#include "include/vector.h"
#include <gtest/gtest.h>
#include <random>
#include <vector>

namespace STL {

template <typename T>
void check_equal(const vector<T> &vec, const std::vector<T> &vec_ref) {
  ASSERT_EQ(vec.size(), vec_ref.size());
  auto itr = vec.begin();
  auto itr_ref = vec_ref.begin();
  for (; itr != vec.end() && itr_ref != vec_ref.end(); itr++, itr_ref++) {
    ASSERT_EQ(*itr, *itr_ref);
  }
  if (!(itr_ref == vec_ref.end() && itr == vec.end())) {
    printf("Wrong ends\n");
  }
  ASSERT_TRUE(itr_ref == vec_ref.end() && itr == vec.end());
}

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

TEST(VectorTests, TestIterator) {
  auto vec = vector<int>({1, 2, 3, 4, 5});
  auto cnt = 1;
  for (int &itr : vec) {
    ASSERT_EQ(itr, cnt);
    itr = 5 - cnt;
    cnt++;
  }
  cnt = 1;
  for (int &itr : vec) {
    ASSERT_EQ(itr, 5 - cnt);
    cnt++;
  }
}

TEST(VectorTests, TestModifier) {
  auto vec = vector<int>({1, 2, 3, 4, 5});
  auto vec_ref = std::vector<int>({1, 2, 3, 4, 5});
  check_equal(vec, vec_ref);

  vec.push_back(6);
  vec_ref.push_back(6);
  check_equal(vec, vec_ref);

  vec.pop_back();
  vec_ref.pop_back();
  check_equal(vec, vec_ref);

  vec.erase(vec.begin());
  vec_ref.erase(vec_ref.begin());
  check_equal(vec, vec_ref);

  vec.erase(vec.begin(), vec.begin() + 1);
  vec_ref.erase(vec_ref.begin(), vec_ref.begin() + 1);
  check_equal(vec, vec_ref);

  vec.clear();
  vec_ref.clear();
  check_equal(vec, vec_ref);
}

TEST(VectorTests, TestInsert) {
  auto vec = vector<int>({1, 2, 3, 4, 5});
  auto vec_ref = std::vector<int>({1, 2, 3, 4, 5});
  check_equal(vec, vec_ref);

  vec.insert(vec.begin() + 1, 2);
  vec_ref.insert(vec_ref.begin() + 1, 2);
  check_equal(vec, vec_ref);

  vec.insert(vec.begin() + 1, 2, 3);
  vec_ref.insert(vec_ref.begin() + 1, 2, 3);
  check_equal(vec, vec_ref);

  auto vec_i = vector<int>({1, 2, 3, 4, 5});
  auto vec_ref_i = std::vector<int>({1, 2, 3, 4, 5});
  vec.insert(vec.begin() + 1, vec_i.begin(), vec_i.end());
  vec_ref.insert(vec_ref.begin() + 1, vec_ref_i.begin(), vec_ref_i.end());
  check_equal(vec, vec_ref);
}

TEST(VectorTests, TestResize) {
  auto vec = vector<int>({1, 2, 3, 4, 5});
  auto vec_ref = std::vector<int>({1, 2, 3, 4, 5});
  check_equal(vec, vec_ref);

  vec.resize(4);
  vec_ref.resize(4);
  check_equal(vec, vec_ref);

  vec.resize(6);
  vec_ref.resize(6);
  check_equal(vec, vec_ref);

  vec.resize(8, 5);
  vec_ref.resize(8, 5);
  check_equal(vec, vec_ref);

  vec.resize(3, 5);
  vec_ref.resize(3, 5);
  check_equal(vec, vec_ref);
}

TEST(VectorTests, TestSwap) {
  auto vec = vector<int>({1, 2, 3, 4, 5});
  auto vec_ref = std::vector<int>({1, 2, 3, 4, 5});
  check_equal(vec, vec_ref);

  auto vec_s = vector<int>({5, 4, 3});
  auto vec_ref_s = std::vector<int>({5, 4, 3});
  check_equal(vec_s, vec_ref_s);

  vec.swap(vec_s);
  vec_ref.swap(vec_ref_s);
  check_equal(vec, vec_ref);
  check_equal(vec_s, vec_ref_s);
}

TEST(VectorTests, TestReverse) {
  auto vec = vector<int>({1, 2, 3, 4, 5});
  auto vec_ref = std::vector<int>({1, 2, 3, 4, 5});
  check_equal(vec, vec_ref);

  vec.reserve(3);
  vec_ref.reserve(3);
  check_equal(vec, vec_ref);

  vec.reserve(8);
  vec_ref.reserve(8);
  ASSERT_TRUE(vec.capacity() >= 8);
  check_equal(vec, vec_ref);
}

TEST(VectorTests, TestOperator) {
  auto vec = vector<int>({1, 2, 3, 4, 5});
  auto vec_ref = std::vector<int>({1, 2, 3, 4, 5});
  check_equal(vec, vec_ref);

  for (auto i = 0; i < vec.size(); i++) {
    ASSERT_EQ(vec[i], vec_ref[i]);
  }

  auto vec1 = vec;
  auto vec_ref1 = vec_ref;
  check_equal(vec1, vec_ref1);

  auto vec2 = std::move(vec);
  auto vec_ref2 = std::move(vec_ref);
  ASSERT_TRUE(vec.data() == nullptr && vec_ref.data() == nullptr);
  check_equal(vec2, vec_ref2);

  auto vec3 = vector<int>({1, 2, 3});
  auto vec4 = vector<int>({1, 2, 3});
  auto vec5 = vector<int>({1, 2, 4});
  ASSERT_TRUE(vec3 == vec3);
  ASSERT_TRUE(vec3 == vec4);
  ASSERT_TRUE(vec3 != vec5);
}

TEST(VectorTests, TestBSearch) {
  auto vec = vector<int>();
  auto vec_ref = std::vector<int>();
  for (auto i = 0; i < 100; i += 2) {
    vec.push_back(i);
    vec_ref.push_back(i);
  }
  check_equal(vec, vec_ref);
  // search even: found
  for (auto i = 0; i < 100; i += 2) {
    size_t l = 0;
    size_t r = vec.size() - 1;
    while (l < r) {
      size_t mid = (l + r) / 2;
      if (vec[mid] < i) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    ASSERT_EQ(l, i / 2);
    ASSERT_EQ(vec[l], i);
  }
  // search odd: not found
  for (auto i = 1; i < 99; i += 2) {
    size_t l = 0;
    size_t r = vec.size() - 1;
    while (l < r) {
      size_t mid = (l + r) / 2;
      if (vec[mid] < i) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    ASSERT_EQ(l, i / 2 + 1);
    ASSERT_NE(vec[l], i);
  }
}

template <typename T>
void swap(vector<T> &vec, int i, int j) {
  auto temp = vec[i];
  vec[i] = vec[j];
  vec[j] = temp;
}

template <typename T>
int partition(vector<T> &vec, int l, int r, int p) {
  auto pivot = vec[p];
  swap(vec, p, r);
  p = l;
  for (int i = l; i < r; i++) {
    if (vec[i] < pivot) {
      swap(vec, p, i);
      p++;
    }
  }
  swap(vec, r, p);
  return p;
}

template <typename T>
void qsort(vector<T> &vec, int l, int r) {
  if (l < r) {
    auto p = partition(vec, l, r, random() % (r - l + 1) + l);
    qsort(vec, l, p - 1);
    qsort(vec, p + 1, r);
  }
}

TEST(VectorTests, TestQSort) {
  auto vec = vector<int>();
  auto vec_ref = std::vector<int>();
  for (int i = 0; i < 10000; i++) {
    auto num = static_cast<int>(random() % 1000000);
    vec.push_back(num);
    vec_ref.push_back(num);
  }
  check_equal(vec, vec_ref);
  std::sort(vec_ref.begin(), vec_ref.end());
  qsort(vec, 0, static_cast<int>(vec.size()) - 1);
  check_equal(vec, vec_ref);
}

}  // namespace STL
