#include <iostream>
#include "s21_map.h"
#include <typeinfo>

int main() {

  s21::Tree<int, int> tree = s21::Tree<int, int>();  // создаем пустое дерево
  tree.Insert(12);  // узел станет корнем дерева
  tree.Insert(2);   // пойдет в левую часть
  tree.Insert(16);  // пойдет в правую часть
  tree.Insert(13);  // пойдет правую, потом в левую часть

    tree.Remove(12);
    tree.Remove(2);
    tree.Remove(13);
    std::cout << "Размер: " << tree.size << std::endl;
    std::cout << "Максимальное число: " << tree.max << std::endl;
    std::cout << "Минимальное число: " << tree.min << std::endl;
    std::cout << "ключ корня: " << tree.root->key << std::endl;
    // std::cout << "право корня: " << tree.root->right->key << std::endl;
    // std::cout << "top леов корня: " << tree.root->left->key << std::endl;


}