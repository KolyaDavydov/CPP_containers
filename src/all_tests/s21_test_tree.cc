#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

#include "../tree.h"

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

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
