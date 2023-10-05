#ifndef CPP2_SRC_S21_MAP_H_
#define CPP2_SRC_S21_MAP_H_

#include "tree.h"
#include <utility> // для std::pair
namespace s21 {
template<typename T, typename V>
class map {
    public:
    // внутриклассовые переопределения типов (типичные для стандартной библиотеки STL), принятые для удобства восприятия кода класса:
    using key_type = T;
    using mapped_type = V;
    using default_value = mapped_type&;
    using value_type = std::pair<const key_type, mapped_type>;
    using iterator = Iterator<value_type, V>;
    // using const_iterator = ConstIterator<value_type, V>;
    using size_type = size_t;

    // КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ
    map();

    // ПАРАМЕТРЫ
    Tree<value_type, mapped_type> tree_in_map;

// методы для итеррирования по элементам контейнера
    iterator begin();
    iterator end();

    // методы для изменения контейнера

    // вставляет узел и возвращает итератор туда, где находится элемент в контейнере, и логическое значение, обозначающее, имела ли место вставка
    std::pair<iterator, bool> insert(const value_type& value);


    // вспомогательные методы
    // проверка что такого ключа нет в словаре
    bool check_unique(const value_type& value);
};

// инициализируем пустой словарь где в качестве параметра пустое дерево
template<typename T, typename V>
map<T, V>::map() : tree_in_map() {}

// методы для итеррирования по элементам контейнера
    template<typename T, typename V>
    typename map<T, V>::iterator map<T, V>::begin() {
        Node<T, V>* node = tree_in_map.root;
        while (node->left != nullptr) {
            node = node->left;
        }
        return iterator(node, tree_in_map.root);
    }

    template<typename T, typename V>
    typename map<T, V>::iterator map<T, V>::end() {
        Node<T, V>* node = tree_in_map.root;
        while (node->right != nullptr) {
            node = node->right;
        }
        return iterator(node, tree_in_map.root);
    }

// методы для изменения контейнера

    // вставляет узел и возвращает итератор туда, где находится элемент в контейнере, и логическое значение, обозначающее, имела ли место вставка
    template<typename T, typename V>
    std::pair<typename map<T, V>::iterator, bool> map<T, V>::insert(const value_type& value) {

    }

    // Вспомогательные методы

    // проверяет что переданного ключа нет в словаре
    // возвращает false, если ключа нет
template<typename T, typename V>
bool map<T, V>::check_unique(const value_type& value) {
    auto i = this->begin();
    for (; i != this->end(); i++) {
        if (i->first == value.first) {
            return true;
        }
    }
    return false;
}
}


#endif  // CPP2_SRC_S21_MAP_H_