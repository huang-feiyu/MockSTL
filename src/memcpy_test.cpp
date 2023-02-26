#include "include/memcpy.h"
#include <gtest/gtest.h>

TEST(MemcpyTests, TestNormal) {
  const char *str = "abcdef";
  auto size = sizeof(str);
  char *str_cpy = static_cast<char *>(malloc(size));
  char *str_cpy_half = static_cast<char *>(malloc(size / 2));

  ASSERT_EQ(imemcpy(str_cpy, str, size), str_cpy);
  for (auto i = 0; i < size; i++) {
    ASSERT_EQ(str_cpy[i], str[i]);
  }

  ASSERT_EQ(imemcpy(str_cpy_half, str + size / 2, size / 2), str_cpy_half);
  for (auto i = 0; i < size / 2; i++) {
    ASSERT_EQ(str_cpy_half[i], str[i + size / 2]);
  }

  free(str_cpy);
  free(str_cpy_half);
}

TEST(MemcpyTests, TestNULL) {
  const char *str = "abcdef";
  auto size = sizeof(str);
  char *str_cpy = static_cast<char *>(malloc(size));
  const char *str_null = nullptr;
  char *str_cpy_null = nullptr;

  // dst: NULL; src: NULL
  ASSERT_EQ(imemcpy(str_cpy_null, str_null, size), nullptr);
  // dst: NULL; src: not NULL
  ASSERT_EQ(imemcpy(str_cpy_null, str, size), nullptr);
  // dst: not NULL; src: NULL
  ASSERT_EQ(imemcpy(str_cpy, str_null, size), nullptr);
  // dst: not NULL; src: not NULL
  ASSERT_EQ(imemcpy(str_cpy, str, size), str_cpy);
  for (auto i = 0; i < size; i++) {
    ASSERT_EQ(str_cpy[i], str[i]);
  }

  free(str_cpy);
}

TEST(MemcpyTests, TestOverlap) {
  const char *str = "abcdef";
  auto size = sizeof(str);

  ASSERT_EQ(imemcpy((void *)(str + 1), str, size - 1), nullptr);
  ASSERT_EQ(imemcpy((void *)(str), str, size), nullptr);
  ASSERT_EQ(imemcpy((void *)(str - 1), str, size + 1), nullptr);
}
