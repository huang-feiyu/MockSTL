#include "include/list.h"
#include <gtest/gtest.h>
#include <list>

namespace STL {

template <typename T>
void check_equal(list<T> &list, std::list<T> &list_ref) {
  ASSERT_EQ(list.size(), list_ref.size());
  auto itr_ref = list_ref.begin();
  for (auto itr = list.begin(); itr != list.end(); itr++, itr_ref++) {
    ASSERT_EQ(*itr, *itr_ref);
  }
}

TEST(ListTests, TestConstructor) {
  list<int> list1;
  std::list<int> list1_ref;
  check_equal(list1, list1_ref);
  ASSERT_TRUE(list1.empty());

  auto list2 = list<int>({1, 2, 3, 4, 5});
  auto list2_ref = std::list({1, 2, 3, 4, 5});
  check_equal(list2, list2_ref);

  auto list3 = list2;
  auto list3_ref = list2_ref;
  ASSERT_TRUE(list2 == list3);
  check_equal(list3, list3_ref);

  auto list4 = std::move(list2);
  auto list4_ref = std::move(list2_ref);
  ASSERT_TRUE(list3 == list4);
  check_equal(list4, list4_ref);
}

TEST(ListTests, TestRawIterator) {
  auto n1 = new list<int>::node(1);
  auto n2 = new list<int>::node(2);
  auto n3 = new list<int>::node(3);
  auto n4 = new list<int>::node(4);
  auto n5 = new list<int>::node(5);
  n1->next_ = n2;
  n2->next_ = n3;
  n3->next_ = n4;
  n4->next_ = n5;
  n5->next_ = n1;
  n5->prev_ = n4;
  n4->prev_ = n3;
  n3->prev_ = n2;
  n2->prev_ = n1;
  n1->prev_ = n5;

  size_t cnt;
  auto begin = list<int>::Iterator(n1);
  auto end = list<int>::Iterator(n5);

  cnt = 1;
  for (auto itr = begin; itr != end; itr++, cnt++) {
    ASSERT_EQ(cnt, *itr);
  }

  cnt = 1;
  for (auto itr = begin; itr != end; ++itr, cnt++) {
    ASSERT_EQ(cnt, *itr);
  }

  cnt = 5;
  for (auto itr = end; itr != begin; itr--, cnt--) {
    ASSERT_EQ(cnt, *itr);
  }

  cnt = 5;
  for (auto itr = end; itr != begin; --itr, cnt--) {
    ASSERT_EQ(cnt, *itr);
  }

  ASSERT_TRUE(begin != end);
  begin = end;
  ASSERT_TRUE(begin == end);
}

TEST(ListTests, TestModifier) {
  auto list = STL::list<int>({1, 2, 3, 4, 5});
  auto list_ref = std::list({1, 2, 3, 4, 5});
  check_equal(list, list_ref);

  list.push_back(6);
  list_ref.push_back(6);
  check_equal(list, list_ref);

  list.pop_back();
  list_ref.pop_back();
  check_equal(list, list_ref);

  list.push_front(0);
  list_ref.push_front(0);
  check_equal(list, list_ref);

  list.pop_front();
  list_ref.pop_front();
  check_equal(list, list_ref);

  list.erase(list.begin());
  list_ref.erase(list_ref.begin());
  check_equal(list, list_ref);

  list.insert(list.begin(), 0);
  list_ref.insert(list_ref.begin(), 0);
  check_equal(list, list_ref);

  auto list_s = STL::list<int>({1, 2, 3});
  auto list_s_ref = std::list<int>({1, 2, 3});
  check_equal(list_s, list_s_ref);
  list_s.swap(list);
  list_s_ref.swap(list_ref);
  check_equal(list_s, list_s_ref);
  check_equal(list, list_ref);

  STL::list<int> list_empty;
  list.clear();
  ASSERT_TRUE(list == list_empty);
}

}  // namespace STL
