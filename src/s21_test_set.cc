#include <gtest/gtest.h>

#include "s21_set.h"
#include "set"

#define s21_EPS 1e-7

TEST(Set, DefaultConstructor) {
  s21::set<int> s21set;
  EXPECT_EQ(s21set.size(), 0);
}

TEST(Set, Insert) {
  s21::set<int> s21set;
  s21set.insert(1);
  EXPECT_EQ(s21set.size(), 1);
}
TEST(Set, InsertMany) {
  s21::set<int> s21set;
  s21set.insert(1);
  s21set.insert(11);
  EXPECT_EQ(s21set.size(), 2);
}

// TEST(Map, DefaultConstructor) {
//   s21::set<int> s21set;
//   s21set.insert({1, 2, 3});
//   EXPECT_EQ(s21set.size(), 1);
// }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
