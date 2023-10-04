#include <gtest/gtest.h>
#include "tree.h"
#include <iostream>

// проверка конструктора для узла Node c передаваемым значением ключа
TEST(Tree, Node_constructor) {
    s21::Node<int, int> node(25);
    ASSERT_EQ(node.key, 25);
}
// проверка конструктора инициализирующего пустое дерево
TEST(Tree, Tree_constructor) {
    s21::Tree<int, int> tree = s21::Tree<int, int>();
    ASSERT_EQ(tree.root, nullptr);
}

// провека как вставляется узел в дерево и как дерево удаляется
TEST(Tree, Tree_InsertNodeAndClearTree) {
    s21::Tree<int, int> tree = s21::Tree<int, int>(); // создаем пустое дерево
    ASSERT_EQ(tree.root, nullptr);

    s21::Node<int, int> *node = tree.Insert(12); // узел станет корнем дерева
    ASSERT_EQ(node->key, 12);
    ASSERT_EQ(tree.root, node);

    tree.Insert(2); // пойдет в левую часть
    ASSERT_EQ(tree.root->left->key, 2);
    
    tree.Insert(16); // пойдет в правую часть
    ASSERT_EQ(tree.root->right->key, 16);

    tree.Insert(13); // пойдет правую, потом в левую часть
    ASSERT_EQ(tree.root->right->left->key, 13);

    tree.ClearTree(tree.root);
    ASSERT_EQ(tree.root, nullptr);
}

// провека как вставляется узел в дерево и как дерево удаляется
TEST(Tree, CopyTree) {
    // создаем пустое дерево и заносим туда узлы с различными ключами
    s21::Tree<int, int> tree = s21::Tree<int, int>(); // создаем пустое дерево
    tree.Insert(12); // узел станет корнем дерева
    tree.Insert(2); // пойдет в левую часть
    tree.Insert(16); // пойдет в правую часть
    tree.Insert(13); // пойдет правую, потом в левую часть

    // СОздаем другое пустое дерево и копируем туда все узлы
    s21::Tree<int, int> copyTree = s21::Tree<int, int>();
    copyTree.root = tree.CopyTree(tree.root);
        
    ASSERT_EQ(tree.root->key, copyTree.root->key);
    ASSERT_EQ(tree.root->right->left->key, copyTree.root->right->left->key);
}


// ПРоверка конструктора для дерева
TEST(Tree, CopyConstructorTree) {
    // создаем пустое дерево и заносим туда узлы с различными ключами
    s21::Tree<int, int> tree = s21::Tree<int, int>(); // создаем пустое дерево
    tree.Insert(12); // узел станет корнем дерева
    tree.Insert(2); // пойдет в левую часть
    tree.Insert(16); // пойдет в правую часть
    tree.Insert(13); // пойдет правую, потом в левую часть

    // СОздаем другое с использованием конструктора копирования
    s21::Tree<int, int> copyTree(tree);
        
    ASSERT_EQ(tree.root->key, copyTree.root->key);
    ASSERT_EQ(tree.root->right->left->key, copyTree.root->right->left->key);
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
