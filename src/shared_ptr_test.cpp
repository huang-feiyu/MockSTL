#include "include/shared_ptr.h"
#include <gtest/gtest.h>
#include <memory>
#include "include/vector.h"

namespace STL {

struct Foo {
  Foo() { std::cout << "Foo...\n"; }
  ~Foo() { std::cout << "~Foo...\n"; }
};

TEST(VectorTests, TestConstructor) {
  shared_ptr<Foo> sh1;
  std::shared_ptr<Foo> sh1_ref;
  ASSERT_EQ(sh1.use_count(), sh1_ref.use_count());

  auto sh2 = shared_ptr<Foo>(new Foo());
  auto sh2_ref = std::shared_ptr<Foo>(new Foo());
  ASSERT_EQ(sh2.use_count(), sh2_ref.use_count());

  auto sh3 = shared_ptr<Foo>(sh2);
  auto sh3_ref = std::shared_ptr<Foo>(sh2_ref);
  ASSERT_EQ(sh3.use_count(), sh3_ref.use_count());
  ASSERT_EQ(sh3.get(), sh2.get());

  auto sh4 = shared_ptr<Foo>(std::move(sh2));
  auto sh4_ref = std::shared_ptr<Foo>(std::move(sh2_ref));
  ASSERT_EQ(sh4.use_count(), sh4_ref.use_count());
  ASSERT_EQ(sh4.get(), sh3.get());
}

TEST(VectorTests, TestAssignment) {
  auto sh1 = shared_ptr<Foo>(new Foo());
  auto sh1_ref = std::shared_ptr<Foo>(new Foo());
  ASSERT_EQ(sh1.use_count(), sh1_ref.use_count());

  auto sh2 = sh1;
  auto sh2_ref = sh1_ref;
  ASSERT_EQ(sh2.use_count(), sh2_ref.use_count());
  ASSERT_EQ(sh2.get(), sh1.get());

  auto sh3 = std::move(sh1);
  auto sh3_ref = std::move(sh1_ref);
  ASSERT_EQ(sh3.use_count(), sh3_ref.use_count());
  ASSERT_EQ(sh3.get(), sh2.get());
}

TEST(VectorTests, TestModifier) {
  auto foo = new Foo();
  auto foo_ref = new Foo();
  auto sh1 = shared_ptr<Foo>(foo);
  auto sh1_ref = std::shared_ptr<Foo>(foo_ref);
  ASSERT_EQ(sh1.use_count(), sh1_ref.use_count());

  {
    auto sh2 = sh1;
    auto sh2_ref = sh1_ref;
    ASSERT_EQ(sh2.use_count(), sh2_ref.use_count());
    sh2.reset();
    sh2_ref.reset();
    ASSERT_EQ(sh2.use_count(), sh2_ref.use_count());
  }

  auto sh3 = std::move(sh1);
  auto sh3_ref = std::move(sh1_ref);
  ASSERT_EQ(sh3.use_count(), sh3_ref.use_count());

  auto foo_r = new Foo();
  auto foo_r_ref = new Foo();
  sh3.reset(foo_r);
  sh3_ref.reset(foo_r_ref);
  ASSERT_EQ(sh3.use_count(), sh3_ref.use_count());
  ASSERT_TRUE(sh3.get() == foo_r);

  ASSERT_TRUE(sh3 && sh3_ref);
}

TEST(VectorTests, TestSwap) {
  auto sh1 = shared_ptr<Foo>(new Foo());
  auto sh1_ref = std::shared_ptr<Foo>(new Foo());
  ASSERT_EQ(sh1.use_count(), sh1_ref.use_count());

  auto sh2 = shared_ptr<Foo>(new Foo());
  auto sh2_ref = std::shared_ptr<Foo>(new Foo());
  ASSERT_EQ(sh2.use_count(), sh2_ref.use_count());

  auto sh3 = sh2;
  auto sh3_ref = sh2_ref;
  ASSERT_EQ(sh3.use_count(), sh3_ref.use_count());

  sh1.swap(sh2);
  sh1_ref.swap(sh2_ref);
  ASSERT_TRUE(sh1.get() != sh2.get() && sh1.get() == sh3.get());
  ASSERT_TRUE(sh1_ref.get() != sh2_ref.get() && sh1_ref.get() == sh3_ref.get());

  ASSERT_NE(sh1.use_count(), sh2.use_count());
  ASSERT_EQ(sh1.use_count(), sh3.use_count());
  ASSERT_NE(sh1_ref.use_count(), sh2_ref.use_count());
  ASSERT_EQ(sh1_ref.use_count(), sh3_ref.use_count());

  ASSERT_EQ(sh1.use_count(), sh1_ref.use_count());
  ASSERT_EQ(sh2.use_count(), sh2_ref.use_count());
}

TEST(VectorTests, TestDereference) {
  auto vec1 = new vector<int>();
  auto vec2 = new std::vector<int>();
  auto sh1 = shared_ptr<vector<int>>(vec1);
  auto sh1_ref = std::shared_ptr<std::vector<int>>(vec2);
  ASSERT_EQ(sh1.use_count(), sh1_ref.use_count());

  for (int i = 0; i < 100; i++) {
    sh1->push_back(i);
    sh1_ref->push_back(i);
  }
  ASSERT_EQ(sh1->size(), sh1_ref->size());

  for (int i = 0; i < 50; i++) {
    (*sh1).pop_back();
    (*sh1_ref).pop_back();
  }
  ASSERT_EQ(sh1->size(), sh1_ref->size());
}

}  // namespace STL
