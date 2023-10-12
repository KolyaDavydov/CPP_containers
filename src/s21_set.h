#ifndef CPP2_SRC_S21_SET_H_
#define CPP2_SRC_S21_SET_H_
#include "tree.h"

namespace s21 {

template <typename Key>
class set {
  {
   public:
    // attributes
    using key_type = Key;
    using value_type = Key;
    using reference = value_type &;
    using const_reference = const value_type &;
    using tree_type = Tree<key_type, value_type>;
    using iterator = Iterator<Key>;
    // using iterator = SetIterator<Key>;
    // using const_iterator = SetConstIterator<Key>;
    using size_type = std::size_t;

    // tree_type *tree_;
    set() : tree_(new tree_type{}) {}

    set(std::initializer_list<value_type> const &items) {
      for (value_type i : items) insert(i);
    }

    set(const set &v) {}

    set(const set &other) : tree_(new tree_type(*other.tree_)) {}

    set(set && other) noexcept
        : tree_(new tree_type(std::move(*other.tree_))) {}

    set(set && v) noexcept {}

    ~set() {
      delete tree_;
      tree_ = nullptr;
    }

    std::pair<iterator, bool> insert(const value_type &value) {
      return tree_->Insert(value);
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

    iterator find(const key_type &key) noexcept { return tree_->Search(key); }

    const_iterator find(const key_type &key) const {
      return tree_->Search(key);
    }

    void clear() { tree_->ClearTree(root); };

    // operator overload

    set &operator=(const set &other) {
      *tree_ = *other.tree_;
      return *this;
    }

    set &operator=(set &&other) noexcept {
      *tree_ = std::move(*other.tree_);
      return *this;
    }
    // void erase(iterator pos);

    // void swap(set & other);

    // void merge(set & other);

    bool empty() {
      if (this->tree_.GetSize() == 0) {
        return true;
      } else {
        return false;
      }
    }

    size_type size() { return this->tree_.GetSize(); }

    size_type max_size() { return this->tree_.MaxSize(); }
  }

 private:
  tree_type *tree_;
};
}  // namespace s21

#endif  // CPP2_SRC_S21_SET_H_