#include "include/string.h"
#include <gtest/gtest.h>
#include <string>

namespace STL {

void check_equal(const string &str, const std::string &str_ref) {
  ASSERT_EQ(str.size(), str_ref.size());
  ASSERT_TRUE(strcmp(str.c_str(), str_ref.c_str()) == 0);
}

TEST(StringTests, TestAll) {
  string str1;
  std::string str1_ref;
  check_equal(str1, str1_ref);

  auto str2 = string("abc");
  auto str2_ref = std::string("abc");
  check_equal(str2, str2_ref);

  auto str3 = string(str2);
  auto str3_ref = std::string(str2_ref);
  check_equal(str3, str3_ref);
  ASSERT_EQ(str3, str2);

  auto str4 = string(std::move(str2));
  auto str4_ref = std::string(std::move(str2_ref));
  check_equal(str4, str4_ref);
  ASSERT_EQ(str4, str3);

  string str5 = (string) "abc";
  std::string str5_ref = "abc";
  check_equal(str5, str5_ref);

  string str6 = str5;
  std::string str6_ref = str5_ref;
  check_equal(str6, str6_ref);

  string str7 = std::move(str5);
  std::string str7_ref = std::move(str5_ref);
  check_equal(str7, str7_ref);
}

}  // namespace STL
