#ifndef CPP2_SRC_S21_SET_H_
#define CPP2_SRC_S21_SET_H_

#include <initializer_list>
#include <utility>  // для std::pair

#include "tree.h"

namespace s21 {

template <typename Key>
class set {
 public:
  // attributes
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using tree_type = Tree<key_type, value_type>;
  using node_type = std::pair<const key_type, value_type>;
  using iterator = Iterator<key_type, value_type>;
  using const_iterator = Iterator<key_type, value_type>;
  using size_type = std::size_t;

  set() : tree_() {}

  set(const set &other) : tree_(other.tree_) {}
  set(set &&other) : tree_(std::move(*other.tree_)) { other.clear(); }

  ~set() {}

  std::pair<iterator, bool> insert(const value_type &value);
  // std::pair<iterator, bool> insert(const key_type &value) {
  //   return tree_.Insert(value);
  // }

  // std::pair<typename set<key_type>::iterator, bool> set<key_type>::insert(
  //     const key_type &key) {
  //   return insert(std::pair<key_type, node_type>(key, key));
  // }
  set(std::initializer_list<value_type> const &items) : set() {
    for (value_type i : items) insert(i);
  }
  // iterators

  iterator begin() noexcept {
    Node<key_type, value_type> *node = this->tree_.GetRoot();
    while (node->left != nullptr) {
      node = node->left;
    }
    return iterator(node, tree_.GetRoot());
  }

  const_iterator begin() const noexcept {
    Node<key_type, value_type> *node = this->tree_.GetRoot();
    while (node->left != nullptr) {
      node = node->left;
    }
    return iterator(node, tree_.GetRoot());
  }

  iterator end() noexcept {
    Node<key_type, value_type> *node = tree_.GetRoot();
    while (node->right != nullptr) {
      node = node->right;
    }
    return iterator(node, tree_.GetRoot());
  }

  const_iterator end() const noexcept {
    Node<key_type, value_type> *node = tree_.GetRoot();
    while (node->right != nullptr) {
      node = node->right;
    }
    return iterator(node, tree_.GetRoot());
  }

  iterator find(const key_type &key) noexcept { return tree_.Search(key); }

  const_iterator find(const key_type &key) const { return tree_.Search(key); }

  // bool contains(const Key &key) {
  //   Node<key_type, value_type> *node = this->tree_.Search(key);
  //   if (node != nullptr) {
  //     return true;
  //   } else {
  //     return false;
  //   }
  // }

  void clear() { tree_.ClearTree(tree_.GetRoot()); };

  // operator overload

  set &operator=(const set &other) {
    *tree_ = *other.tree_;
    return *this;
  }

  set &operator=(set &&other) noexcept {
    *tree_ = std::move(*other.tree_);
    return *this;
  }
  void erase(iterator pos) {
    if (pos.root_ != nullptr) {
      this->tree_.Remove(pos.node_->key);
    }
  }

  void swap(set &other) { tree_.Swap(other.tree_); }

  void merge(set &other) {
    iterator iter = other.begin();
    while (iter != other.end()) {
      this->insert(iter.node_->key, iter.node_->val);

      iter++;
    }
    this->insert(iter.node_->key, iter.node_->val);
  }

  bool empty() {
    if (this->tree_.GetSize() == 0) {
      return true;
    } else {
      return false;
    }
  }

  size_type size() noexcept { return this->tree_.GetSize(); }

  size_type max_size() noexcept { return this->tree_.MaxSize(); }

  bool check_unique(const value_type &value);

 private:
  tree_type tree_;
};

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type &value) {
  // если value есть в словаре то возвращем пару: <Итератор на это значение,
  //  false>
  if (check_unique(value)) {
    auto r = this->tree_.Search(value);
    return std::make_pair(iterator(r, tree_.GetRoot()), false);
  }

  // если нет такого ключа в словаре то вставляем этот ключ
  this->tree_.Insert(value);
  auto r = this->tree_.Search(value);
  r->val = value;
  return std::make_pair(iterator(r, tree_.GetRoot()), true);
}

// Вспомогательные методы

// проверяет что переданного ключа нет в словаре
// возвращает false, если ключа нет
template <typename Key>
bool set<Key>::check_unique(const value_type &value) {
  if (this->size() > 0) {
    iterator i = this->begin();

    do {
      if (value == i.node_->key) {
        return true;
      }
      i++;
    } while (i.node_->is_max == false);
  }
  return false;
}
}  // namespace s21

#endif  // CPP2_SRC_S21_SET_H_