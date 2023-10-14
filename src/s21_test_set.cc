#include <gtest/gtest.h>

#include "s21_set.h"
#include "set"

#define s21_EPS 1e-7

TEST(Set, DefaultConstructor) {
  s21::set<int> s21set;
  ASSERT_EQ(s21set.GetTree().GetRoot(), nullptr);
  EXPECT_EQ(s21set.size(), 0);
}

TEST(Set, InitializerListConstructor) {
  s21::set<std::string> s21set{"one", "two", "three"};
  EXPECT_EQ(s21set.size(), 3);
  EXPECT_EQ(s21set.GetTree().GetRoot()->key, "one");
}

TEST(Set, CopyConstructor) {
  s21::set<int> set1 = {2, 3, 4, 5, 1};
  s21::set<int> set2(set1);
  EXPECT_EQ(set1.size(), 5);
  EXPECT_EQ(set2.size(), 5);
}

TEST(Set, MoveConstuctor) {
  s21::set<int> s1 = {2, 3, 4, 5, 1};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 5);
  EXPECT_EQ(s1.size(), 0);
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

TEST(Set, Size_Empty) {
  s21::set<std::string> empty_set;
  s21::set<std::string> set33 = {"one",
                                 "two"
                                 "three"};

  EXPECT_TRUE(empty_set.empty());
  EXPECT_EQ(empty_set.size(), 0);
  std::cout << set33.GetTree().GetRoot()->key << std::endl;

  EXPECT_FALSE(set33.empty());
  EXPECT_EQ(set33.size(), 3);
}

TEST(Set, Clear) {
  s21::set<std::string> set = {"one", "two", "three"};
  ASSERT_EQ(set.size(), 3);

  set.clear();
  ASSERT_EQ(set.size(), 0);
}

// вставка std::pair, если такой ключ есть то то не вставляет и возвращает false
TEST(Set, InsertPair) {
  s21::set<int> set11;
  s21::set<int> set12;
  int ins = 3;
  EXPECT_EQ(set11.insert(ins), set12.insert(ins));
  EXPECT_EQ(set11.size(), set12.size());
}

// вставка пары (key, value), если такой ключ есть то то не вставляет и
// возвращает false
TEST(Set, InsertPair1) {
  s21::set<int> set14;
  s21::set<int> set24;

  EXPECT_EQ(set14.insert(3), set24.insert(3));
  EXPECT_EQ(set14.size(), set24.size());
  EXPECT_EQ(set14.GetTree().GetRoot()->key, 3);
  EXPECT_EQ(set24.GetTree().GetRoot()->key, 3);
}

TEST(Set, Erase_and_Begin) {
  s21::set<std::string> m1;
  m1.insert("десять");
  m1.insert("один");
  m1.insert("два");
  m1.insert("двенадцать");
  EXPECT_EQ(m1.size(), 4);

  auto iter = m1.begin();
  EXPECT_EQ(iter.node_->key, "один");

  auto iter2 = m1.end();
  EXPECT_EQ(iter2.node_->key, "двенадцать");

  m1.erase(iter);
  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m1.begin().node_->key, "два");
}

TEST(Set, Swap) {
  s21::set<std::string> m1;
  m1.insert("десять");
  m1.insert("один");
  m1.insert("два");
  m1.insert("двенадцать");
  s21::set<std::string> m2;
  EXPECT_EQ(m1.size(), 4);
  EXPECT_EQ(m2.size(), 0);

  m1.swap(m2);
  EXPECT_EQ(m1.size(), 0);
  EXPECT_EQ(m2.size(), 4);
}

TEST(Set, Merge) {
  s21::set<std::string> m1;
  m1.insert("десять");
  m1.insert("один");
  m1.insert("два");
  m1.insert("двенадцать");
  s21::set<std::string> m2;
  m2.insert("одинадцать");
  m2.insert("три");
  m2.insert("два");

  m1.merge(m2);
  EXPECT_EQ(m1.size(), 6);
}

TEST(Set, Contains) {
  s21::set<std::string> set;

  set.insert("one");
  set.insert("two");
  EXPECT_TRUE(set.contains("two"));
  EXPECT_FALSE(set.contains("tree"));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
