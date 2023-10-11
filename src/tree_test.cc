#include "tree.h"

#include <gtest/gtest.h>

#include <iostream>

#include "s21_map.h"

// проверка конструктора для узла Node c передаваемым значением ключа
TEST(Tree, Node_constructor) {
  s21::Node<int, int> node(25);
  ASSERT_EQ(node.key, 25);
}
// проверка конструктора инициализирующего пустое дерево
TEST(Tree, Tree_constructor) {
  s21::Tree<int, int> tree = s21::Tree<int, int>();
  ASSERT_EQ(tree.GetRoot(), nullptr);
  ASSERT_EQ(tree.GetMax(), 0);
  ASSERT_EQ(tree.GetMin(), 0);
  ASSERT_EQ(tree.GetSize(), 0);
}

// провека как вставляется узел в дерево и как дерево удаляется
TEST(Tree, Tree_InsertNodeAndClearTree) {
  s21::Tree<int, int> tree = s21::Tree<int, int>();  // создаем пустое дерево
  ASSERT_EQ(tree.GetRoot(), nullptr);

  s21::Node<int, int> *node = tree.Insert(12);  // узел станет корнем дерева
  ASSERT_EQ(node->key, 12);
  ASSERT_EQ(tree.GetRoot(), node);

  tree.Insert(2);  // пойдет в левую часть
  ASSERT_EQ(tree.GetRoot()->left->key, 2);

  tree.Insert(16);  // пойдет в правую часть
  ASSERT_EQ(tree.GetRoot()->right->key, 16);

  tree.Insert(13);  // пойдет правую, потом в левую часть
  ASSERT_EQ(tree.GetRoot()->right->left->key, 13);

  tree.ClearTree(tree.GetRoot());
  ASSERT_EQ(tree.GetRoot(), nullptr);
}

// // провека как вставляется узел в дерево и как дерево удаляется
// TEST(Tree, CopyTree) {
//   // создаем пустое дерево и заносим туда узлы с различными ключами
//   s21::Tree<int, int> tree = s21::Tree<int, int>();  // создаем пустое дерево
//   tree.Insert(12);  // узел станет корнем дерева
//   tree.Insert(2);   // пойдет в левую часть
//   tree.Insert(16);  // пойдет в правую часть
//   tree.Insert(13);  // пойдет правую, потом в левую часть

//   // СОздаем другое пустое дерево и копируем туда все узлы
//   s21::Tree<int, int> copyTree = s21::Tree<int, int>();
//   copyTree.SetRoot(tree.CopyTree(tree.GetRoot())) = ;

//   ASSERT_EQ(tree.root->key, copyTree.root->key);
//   ASSERT_EQ(tree.root->right->left->key, copyTree.root->right->left->key);
// }

// ПРоверка конструктора для дерева
TEST(Tree, CopyConstructorTree) {
  // создаем пустое дерево и заносим туда узлы с различными ключами
  s21::Tree<int, int> tree = s21::Tree<int, int>();  // создаем пустое дерево
  tree.Insert(12);  // узел станет корнем дерева
  tree.Insert(2);   // пойдет в левую часть
  tree.Insert(16);  // пойдет в правую часть
  tree.Insert(13);  // пойдет правую, потом в левую часть

  // СОздаем другое с использованием конструктора копирования
  s21::Tree<int, int> copyTree(tree);

  ASSERT_EQ(tree.GetRoot()->key, copyTree.GetRoot()->key);
  ASSERT_EQ(tree.GetRoot()->right->left->key,
            copyTree.GetRoot()->right->left->key);

  ASSERT_EQ(tree.GetMax(), copyTree.GetMax());
  ASSERT_EQ(tree.GetMin(), copyTree.GetMin());
  ASSERT_EQ(tree.GetSize(), copyTree.GetSize());
}

// ПРоверка оператора присваивания переносом
TEST(Tree, OperatorTree) {
  // создаем пустое дерево и заносим туда узлы с различными ключами
  s21::Tree<int, int> tree = s21::Tree<int, int>();  // создаем пустое дерево
  tree.Insert(12);  // узел станет корнем дерева
  tree.Insert(2);   // пойдет в левую часть
  tree.Insert(16);  // пойдет в правую часть
  tree.Insert(13);  // пойдет правую, потом в левую часть

  // Используем перезагруженный оператор
  s21::Tree<int, int> moveTree = tree;

  ASSERT_EQ(tree.GetRoot()->key, moveTree.GetRoot()->key);
  ASSERT_EQ(tree.GetRoot()->right->left->key,
            moveTree.GetRoot()->right->left->key);
}

// ПРоверка конструктора итератора
TEST(Tree, IteratorConstructor) {
  // создаем пустое дерево и заносим туда узлы с различными ключами
  s21::Tree<int, int> tree = s21::Tree<int, int>();  // создаем пустое дерево
  tree.Insert(12);  // узел станет корнем дерева
  tree.Insert(2);   // пойдет в левую часть
  tree.Insert(16);  // пойдет в правую часть
  tree.Insert(13);  // пойдет правую, потом в левую часть

  // создаем иттератор через исследуемый конструктор
  s21::Iterator<int, int> iter(tree.GetRoot()->left, tree.GetRoot());

  ASSERT_EQ(tree.GetRoot(), iter.root_);
  ASSERT_EQ(tree.GetRoot()->left, iter.node_);

  ASSERT_EQ(*iter, 2);
}

// ПРоверка перезагруженных операторов итератора (*, ++, --, ==, !=)
TEST(Tree, IteratorOperator) {
  // создаем пустое дерево и заносим туда узлы с различными ключами
  s21::Tree<int, int> tree = s21::Tree<int, int>();  // создаем пустое дерево
  tree.Insert(12);  // узел станет корнем дерева
  tree.Insert(2);   // пойдет в левую часть
  tree.Insert(16);  // пойдет в правую часть
  tree.Insert(13);  // пойдет правую, потом в левую часть
  tree.Insert(0);

  // создаем иттератор c помощью нашего конструктора
  s21::Iterator<int, int> iter(tree.GetRoot()->left, tree.GetRoot());
  s21::Iterator<int, int> iter1(iter.node_,
                                tree.GetRoot());  // для проверки '==' и '!='
  ASSERT_EQ(*iter, 2);

  ++iter;  // 12
  ++iter;  // 13

  ASSERT_EQ(iter != iter1, true);  // 13 != 2
  iter++;                          // 16
  iter++;                          // 16
  iter++;                          // 16
  --iter;                          // 13

  iter--;  // 12
  iter--;  // 2
  iter--;  // 0
  iter--;  // 0
  iter++;  // 2

  ASSERT_EQ(iter == iter1, true);
  ASSERT_EQ(*iter, 2);
}

TEST(Tree, Search) {
  // создаем пустое дерево и заносим туда узлы с различными ключами
  s21::Tree<int, int> tree = s21::Tree<int, int>();  // создаем пустое дерево
  tree.Insert(12);  // узел станет корнем дерева
  tree.Insert(2);   // пойдет в левую часть
  tree.Insert(16);  // пойдет в правую часть
  tree.Insert(13);  // пойдет правую, потом в левую часть

  // tree.Search(2)->key ;
  ASSERT_EQ(tree.Search(2)->key, 2);
  // ASSERT_EQ(*iter, 2);
}

TEST(Tree, Remove) {
  // создаем пустое дерево и заносим туда узлы с различными ключами
  s21::Tree<int, int> tree = s21::Tree<int, int>();  // создаем пустое дерево
  tree.Insert(12);  // узел станет корнем дерева
  tree.Insert(2);   // пойдет в левую часть
  tree.Insert(16);  // пойдет в правую часть
  tree.Insert(13);  // пойдет правую, потом в левую часть

  tree.Remove(12);
  ASSERT_EQ(tree.GetRoot()->key, 13);
  ASSERT_EQ(tree.GetSize(), 3);

  tree.Remove(2);
  ASSERT_EQ(tree.GetSize(), 2);
}

TEST(Map, DefaultConstructor) {
  s21::map<int, int> m;
  ASSERT_EQ(m.tree_in_map.GetRoot(), nullptr);
}

TEST(Map, InitializerListConstructor) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m.tree_in_map.GetRoot()->key, 1);
  EXPECT_EQ(m.tree_in_map.GetRoot()->val, "one");

  //   EXPECT_EQ(m.at(1), "one");
  //   EXPECT_EQ(m.at(2), "two");
  //   EXPECT_EQ(m.at(3), "three");
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
