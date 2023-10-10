#include <iostream>
#include "s21_map.h"
#include <typeinfo>
#include <map>
int main() {

s21::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
s21::Node<int, int>* nd = m2.tree_in_map.Search(1);
    std::cout << "ключ корня: " << m2.at(6) << std::endl;
    // std::cout << "право корня: " << tree.root->right->key << std::endl;
    // std::cout << "top леов корня: " << tree.root->left->key << std::endl;


}