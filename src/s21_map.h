#ifndef CPP2_SRC_S21_MAP_H_
#define CPP2_SRC_S21_MAP_H_

#include <utility>  // для std::pair

#include "tree.h"
namespace s21 {
template <typename T, typename V>
class map {
 public:
  // внутриклассовые переопределения типов (типичные для стандартной библиотеки
  // STL), принятые для удобства восприятия кода класса:
  using key_type = T;
  using mapped_type = V;

  using value_type = std::pair<const key_type, mapped_type>;
  using iterator = Iterator<T, V>;
  // using const_iterator = ConstIterator<value_type, V>;
  using size_type = size_t;

  // КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ
  map();

  // ПАРАМЕТРЫ
  Tree<key_type, mapped_type> tree_in_map;
  // iterator* iter;

  // возвращает указатель на начало и конец
  iterator begin();
  iterator end();

  // методы для изменения контейнера

  // ВСТАВКА УЗЛОВ
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const T& key, const V& obj);
  std::pair<iterator, bool> insert_or_assign(const T& key, const V& obj);

  // удаление узла
  void erase(iterator pos);

  //смена содержимого контейнера на другое
  void swap(map& other);

  //слияние передаваемого словаря в первый
  void merge(map& other);

  // вспомогательные методы
  // проверка что такого ключа нет в словаре
  bool check_unique(const value_type& value);
};

// инициализируем пустой словарь где в качестве параметра пустое дерево
template <typename T, typename V>
map<T, V>::map() : tree_in_map() {}

// методы для итеррирования по элементам контейнера
template <typename T, typename V>
typename map<T, V>::iterator map<T, V>::begin() {
  Node<T, V>* node = this->tree_in_map.root;
  while (node->left != nullptr) {
    node = node->left;
  }
  return iterator(node, tree_in_map.root);
}

template <typename T, typename V>
typename map<T, V>::iterator map<T, V>::end() {
  Node<T, V>* node = tree_in_map.root;
  while (node->right != nullptr) {
    node = node->right;
  }
  return iterator(node, tree_in_map.root);
}

// методы для изменения контейнера

// вставляет узел и возвращает итератор туда, где находится элемент в
// контейнере, и логическое значение, обозначающее, имела ли место вставка если
// вставка не имела место значит ключ такой уже есть
template <typename T, typename V>
std::pair<typename map<T, V>::iterator, bool> map<T, V>::insert(
    const value_type& value) {
  //если value есть в словаре то возвращем пару: <Итератор на это значение,
  // false>
  if (check_unique(value)) {
    auto r = this->tree_in_map.Search(value.first);
    return std::make_pair(iterator(r, tree_in_map.root), false);
  }

  // если нет такого ключа в словаре то вставляем этот ключ
  this->tree_in_map.Insert(value.first);
  auto r = this->tree_in_map.Search(value.first);
  r->val = value.second;
  return std::make_pair(iterator(r, tree_in_map.root), true);
}

template <typename T, typename V>
std::pair<typename map<T, V>::iterator, bool> map<T, V>::insert(
    const key_type& key, const mapped_type& obj) {
  return insert(std::pair<key_type, mapped_type>(key, obj));
}

template <typename T, typename V>
std::pair<typename map<T, V>::iterator, bool> map<T, V>::insert_or_assign(
    const key_type& key, const mapped_type& obj) {
  //если елюч уже есть
  if (check_unique(std::make_pair(key, obj))) {
    auto r = this->tree_in_map.Search(key);
    r->val = obj;
    return std::make_pair(iterator(r, tree_in_map.root), true);
  }
  // если нет такого ключа в словаре то вставляем этот ключ и значение obj
  this->tree_in_map.Insert(key);
  auto r = this->tree_in_map.Search(key);
  r->val = obj;
  return std::make_pair(iterator(r, tree_in_map.root), true);
}

template <typename T, typename V>
void map<T, V>::erase(iterator pos) {
  if (pos.root_ != nullptr) {
    this->tree_in_map.Remove(pos.node_->key);
  }
}

template <typename T, typename V>
void map<T, V>::swap(map& other) {
  tree_in_map.Swap(other.tree_in_map);
}

template <typename T, typename V>
void map<T, V>::merge(map& other) {
  iterator iter = other.begin();
  while (iter != other.end()) {
    this->insert(iter.node_->key, iter.node_->val);

    iter++;
  }
  this->insert(iter.node_->key, iter.node_->val);
}

// Вспомогательные методы

// проверяет что переданного ключа нет в словаре
// возвращает false, если ключа нет
template <typename T, typename V>
bool map<T, V>::check_unique(const value_type& value) {
  if (this->tree_in_map.size > 0) {
    iterator i = this->begin();

    do {
      if (value.first == i.node_->key) {
        return true;
      }
      i++;
    } while (i.node_->is_max == false);
  }
  return false;
}
}  // namespace s21

#endif  // CPP2_SRC_S21_MAP_H_