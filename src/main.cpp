#include <iostream>
#include "s21_map.h"
#include <typeinfo>

int main() {

   
//     s21::Tree<int, int> tree = s21::Tree<int, int>(); // создаем пустое дерево
//     tree.Insert(12); // узел станет корнем дерева
//     tree.Insert(2); // пойдет в левую часть
//     tree.Insert(16); // пойдет в правую часть
//     tree.Insert(13); // пойдет правую, потом в левую часть
//     tree.Insert(0);
//     tree.Insert(1);

//         s21::Iterator<int, int> iter(tree.root->left, tree.root);

// // ++iter;
// // ++iter;
// // ++iter;
// // ++iter;
// // ++iter;
// // iter++;
// // iter++;
// // iter++;
// // iter--;
// // iter--;
// iter--;

//  std::cout << iter.node_->extreme <<  std::endl;
//   std::cout << iter.node_->key <<  std::endl;

//   std::cout << tree.size <<  std::endl;
 

    s21::Tree<int, int> tree = s21::Tree<int, int>(); // создаем пустое дерево
    tree.Insert(12); // узел станет корнем дерева
    tree.Insert(2); // пойдет в левую часть
    tree.Insert(16); // пойдет в правую часть
    tree.Insert(13); // пойдет правую, потом в левую часть
        tree.Insert(0);
    tree.Insert(1);

    // создаем иттератор c помощью нашего конструктора
    s21::Iterator<int, int> iter(tree.root->left, tree.root);
 

    iter++;
    // iter++;
    // iter++;
    // iter++;
    // --iter;
    // --iter;
    // --iter;
    // --iter;
    // --iter;

    std::cout << iter.node_->is_max <<  std::endl;

}