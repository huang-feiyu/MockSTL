#include "include/unordered_map.h"
#include <gtest/gtest.h>
#include <unordered_map>

namespace STL {

template <typename Key, typename T>
void check_equal(const unordered_map<Key, T> &map, const std::unordered_map<Key, T> &map_ref) {
  ASSERT_EQ(map.size(), map_ref.size());
  auto tmp_map = std::unordered_map<Key, T>();
  for (auto itr = map.begin(); itr != map.end(); itr++) {
    tmp_map[itr->first] = itr->second;
  }
  ASSERT_EQ(tmp_map, map_ref);
}

TEST(UnorderedMapTests, TestConstructor) {
  auto map1 = unordered_map<std::string, int>();
  auto map1_ref = std::unordered_map<std::string, int>();
  check_equal(map1, map1_ref);

  auto map2 = unordered_map<std::string, int>({{std::string("a"), 1},
                                               {std::string("b"), 2},
                                               {std::string("c"), 3},
                                               {std::string("c"), 4},
                                               {std::string("d"), 4},
                                               {std::string("e"), 5},
                                               {std::string("f"), 6}});
  auto map2_ref = std::unordered_map<std::string, int>({{std::string("a"), 1},
                                                        {std::string("b"), 2},
                                                        {std::string("c"), 3},
                                                        {std::string("c"), 4},
                                                        {std::string("d"), 4},
                                                        {std::string("e"), 5},
                                                        {std::string("f"), 6}});
  check_equal(map2, map2_ref);

  auto map3 = unordered_map<std::string, int>(map2);
  auto map3_ref = std::unordered_map<std::string, int>(map2_ref);
  check_equal(map3, map3_ref);
  check_equal(map2, map3_ref);
  check_equal(map3, map2_ref);

  auto map4 = unordered_map<std::string, int>(std::move(map2));
  auto map4_ref = std::unordered_map<std::string, int>(std::move(map2_ref));
  check_equal(map4, map4_ref);
  check_equal(map4, map3_ref);
  check_equal(map3, map4_ref);

  auto map5 = map3;
  auto map5_ref = map3_ref;
  check_equal(map5, map5_ref);

  auto map6 = std::move(map3);
  auto map6_ref = std::move(map3_ref);
  check_equal(map6, map6_ref);
}

TEST(UnorderedMapTests, TestModifier) {
  auto map = unordered_map<std::string, int>(
      {{std::string("a"), 1}, {std::string("b"), 2}, {std::string("c"), 3}, {std::string("c"), 4}});
  auto map_ref = std::unordered_map<std::string, int>(
      {{std::string("a"), 1}, {std::string("b"), 2}, {std::string("c"), 3}, {std::string("c"), 4}});
  check_equal(map, map_ref);

  map.insert({std::string("a"), 2});
  map_ref.insert({std::string("a"), 2});
  check_equal(map, map_ref);
  map.insert({std::string("d"), 4});
  map_ref.insert({std::string("d"), 4});
  check_equal(map, map_ref);

  auto map_r = unordered_map<std::string, int>(
      {{std::string("a"), 5}, {std::string("b"), 4}, {std::string("c"), 3}, {std::string("c"), 4}});
  auto map_r_ref = std::unordered_map<std::string, int>(
      {{std::string("a"), 5}, {std::string("b"), 4}, {std::string("c"), 3}, {std::string("c"), 4}});
  check_equal(map_r, map_r_ref);

  map.swap(map_r);
  map_ref.swap(map_r_ref);
  check_equal(map_r, map_r_ref);
  check_equal(map, map_ref);

  map.erase(map.begin());
  map_ref.erase(map_ref.begin());
  ASSERT_EQ(map.size(), map_ref.size());

  map.clear();
  map_ref.clear();
  check_equal(map, map_ref);
}

TEST(UnorderedMapTests, TestObserver) {
  auto map = unordered_map<std::string, int>(
      {{std::string("a"), 1}, {std::string("b"), 2}, {std::string("c"), 3}, {std::string("c"), 4}});
  auto map_ref = std::unordered_map<std::string, int>(
      {{std::string("a"), 1}, {std::string("b"), 2}, {std::string("c"), 3}, {std::string("c"), 4}});
  check_equal(map, map_ref);

  ASSERT_NE(map.find(std::string("c")), map.end());
  ASSERT_EQ(map.find(std::string("d")), map.end());

  ASSERT_EQ(map.count(std::string("c")), map_ref.count(std::string("c")));
  ASSERT_EQ(map.count(std::string("d")), map_ref.count(std::string("d")));

  ASSERT_EQ(map.at(std::string("c")), map_ref.at(std::string("c")));
  map.at(std::string("c")) = 5;
  map_ref.at(std::string("c")) = 5;
  check_equal(map, map_ref);

  ASSERT_EQ(map[std::string("d")], map_ref[std::string("d")]);
  map[std::string("d")] = 6;
  map_ref[std::string("d")] = 6;
  check_equal(map, map_ref);
}

}  // namespace STL
