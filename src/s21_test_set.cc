#include <gtest/gtest.h>

#include "s21_set.h"
#include "set"

#define s21_EPS 1e-7

TEST(Map, DefaultConstructor) {
  s21::set<int> s21set;
  s21set.insert({1, 1});
  EXPECT_EQ(s21set.max_size(), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
