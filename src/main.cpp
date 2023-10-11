#include <iostream>
#include "s21_map.h"
#include <typeinfo>
#include <map>
int main() {

  s21::map<int, std::string> map;
  std::map<int, std::string> map1;

  // Max size is implementation-dependent, but it should be greater than 0
  // EXPECT_GT(map.max_size(), map1.max_size());
    std::cout << "ключ корня: " << map.max_size() << std::endl;
    std::cout << "ключ корня: " << std::numeric_limits<size_t>::max() / 2 << std::endl;
    // std::cout << "право корня: " << tree.root->right->key << std::endl;
    // std::cout << "top леов корня: " << tree.root->left->key << std::endl;


}