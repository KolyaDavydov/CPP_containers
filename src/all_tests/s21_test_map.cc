#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <map>

#include "../s21_map.h"

TEST(Map, DefaultConstructor) {
  s21::map<int, int> m;
  ASSERT_EQ(m.tree_in_map.GetRoot(), nullptr);
}

TEST(Map, InitializerListConstructor) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m.tree_in_map.GetRoot()->key, 1);
  EXPECT_EQ(m.tree_in_map.GetRoot()->val, "one");
}

TEST(Map, CopyConstructor) {
  s21::map<int, int> m1 = {{2, 2}, {3, 3}, {4, 4}, {5, 5}, {1, 1}};
  s21::map<int, int> m2(m1);
  EXPECT_EQ(m1.size(), 5);
  EXPECT_EQ(m2.size(), 5);
}

TEST(Map, Size_Empty) {
  s21::map<int, std::string> empty_map;
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_TRUE(empty_map.empty());
  EXPECT_EQ(empty_map.size(), 0);

  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3);
}

TEST(Map, At) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> map1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(map.at(2), map1.at(2));
  EXPECT_THROW(map.at(4), std::out_of_range);
}

TEST(Map, Brackets) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_THROW(map.at(4), std::out_of_range);
  map[2] = "TWO";
  EXPECT_EQ(map[2], "TWO");
}

TEST(Map, Clear) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
  ASSERT_EQ(map.size(), 3);

  map.clear();
  ASSERT_EQ(map.size(), 0);
}

// вставка std::pair, если такой ключ есть то то не вставляет и возвращает false
TEST(Map, InsertPair) {
  s21::map<int, int> m1;
  s21::map<int, int> m2;
  std::pair<int, int> pair = {3, 1};
  EXPECT_EQ(m1.insert(pair).second, m2.insert(pair).second);
  EXPECT_EQ(m1.size(), m2.size());
}

// вставка пары (key, value), если такой ключ есть то то не вставляет и
// возвращает false
TEST(Map, InsertPair1) {
  s21::map<int, int> m1;
  s21::map<int, int> m2;

  EXPECT_EQ(m1.insert(1, 3).second, m2.insert(2, 3).second);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1.tree_in_map.GetRoot()->key, 1);
  EXPECT_EQ(m2.tree_in_map.GetRoot()->key, 2);
}

TEST(Map, Insert_or_assign) {
  s21::map<int, std::string> m1;
  m1.insert_or_assign(1, "один");
  m1.insert_or_assign(2, "два");
  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m1.tree_in_map.GetRoot()->val, "один");

  m1.insert_or_assign(1, "уже не один");
  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m1.tree_in_map.GetRoot()->val, "уже не один");
}

TEST(Map, Erase_and_Begin) {
  s21::map<int, std::string> m1;
  m1.insert_or_assign(10, "десять");
  m1.insert_or_assign(1, "один");
  m1.insert_or_assign(2, "два");
  m1.insert_or_assign(12, "двенадцать");
  EXPECT_EQ(m1.size(), 4);
  EXPECT_EQ(m1.tree_in_map.GetRoot()->val, "десять");

  auto iter = m1.begin();
  EXPECT_EQ(iter.node_->key, 1);

  auto iter2 = m1.end();
  EXPECT_EQ(iter2.node_->key, 12);

  m1.erase(iter);
  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m1.begin().node_->key, 2);
}

TEST(Map, Swap) {
  s21::map<int, std::string> m1;
  m1.insert_or_assign(10, "десять");
  m1.insert_or_assign(1, "один");
  m1.insert_or_assign(2, "два");
  m1.insert_or_assign(12, "двенадцать");
  s21::map<int, std::string> m2;
  EXPECT_EQ(m1.size(), 4);
  EXPECT_EQ(m2.size(), 0);

  m1.swap(m2);
  EXPECT_EQ(m1.size(), 0);
  EXPECT_EQ(m2.size(), 4);
  EXPECT_EQ(m2.tree_in_map.GetRoot()->val, "десять");
  EXPECT_EQ(m2.tree_in_map.GetMax(), 12);
  EXPECT_EQ(m2.tree_in_map.GetMin(), 1);
}

TEST(Map, Merge) {
  s21::map<int, std::string> m1;
  m1.insert_or_assign(10, "десять");
  m1.insert_or_assign(1, "один");
  m1.insert_or_assign(2, "два");
  m1.insert_or_assign(12, "двенадцать");
  s21::map<int, std::string> m2;
  m2.insert_or_assign(11, "одинадцать");
  m2.insert_or_assign(3, "три");
  m2.insert_or_assign(2, "два");

  m1.merge(m2);
  EXPECT_EQ(m1.size(), 6);
  //   EXPECT_EQ(m2.tree_in_map.size, 4);
  //   EXPECT_EQ(m2.tree_in_map.root->val, "десять");
  //   EXPECT_EQ(m2.tree_in_map.max, 12);
  //   EXPECT_EQ(m2.tree_in_map.min, 1);
}

TEST(Map, Contains) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
