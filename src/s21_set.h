#ifndef CPP2_SRC_S21_SET_H_
#define CPP2_SRC_S21_SET_H_
#include "tree_set.h"

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
    using tree_type = Tree<value_type>;
    using iterator = typename tree_type::Iterator;
    using const_iterator = const typename tree_type::Iterator;
    using size_type = std::size_t;

    set() : tree_(new tree_type{}) {}

    set(std::initializer_list<value_type> const &items) {
      for (value_type i : items) insert(i);
    }

    set(const Set &v) {}

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

    iterator begin() noexcept { return tree_->begin(); }

    const_iterator begin() const noexcept { return tree_->begin(); }

    iterator end() noexcept { return tree_->end(); }

    const_iterator end() const noexcept { return tree_->end(); }

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
  }

 private:
  tree_type *tree_;
};
}  // namespace s21

#endif  // CPP2_SRC_S21_SET_H_