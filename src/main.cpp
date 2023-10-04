#include <iostream>
#include "tree.h"

int main() {

    s21::Tree<int, int> tree = s21::Tree<int, int>();
    s21::Node<int, int> *node = tree.Insert(12);
    // s21::Node<int, int> *node1 = tree.Insert(1);
    s21::Node<int, int> *node1 = tree.Insert(2);
    std::cout << node << std::endl;
    std::cout << node1 << std::endl;
    std::cout << tree.root << std::endl;
    
}