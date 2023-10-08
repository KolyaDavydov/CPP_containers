#include <iostream>
#include "s21_map.h"
#include <typeinfo>

int main() {

    s21::map<int, std::string> m;
    std::pair<int, std::string> pair1 = {1, "one"};
    std::pair<int, std::string> pair2 = {2, "two"};
    std::pair<int, std::string> pair3 = {3, "три"};
    std::pair<int, std::string> pair4 = {4, "четыре"};
    std::pair<int, std::string> pair5 = {1, "one-пять"};
    // 
m.insert(pair1);
    std::cout << m.insert(pair1).second << "asd" <<  std::endl;
    
    m.insert(pair2);
    m.insert(pair3);
    m.insert(pair4);
    m.insert(pair5);
    std::cout << m.tree_in_map.Search(1)->val << "asd" <<  std::endl;

    

}