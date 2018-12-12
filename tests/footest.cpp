#include "gtest/gtest.h"
#include "foo.cpp"

namespace {

TEST(StaticTest, TestTrue) {
  EXPECT_EQ(0, 0);
}

TEST(FooTest, TestSum) {
  Foo f = Foo(1,2);
  EXPECT_EQ(f.sum(), 3);
}
}

