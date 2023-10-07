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
    using tree_type = Tree<value_type>;
    using iterator = typename tree_type::Iterator;
    using const_iterator = const typename tree_type::Iterator;
    using size_type = std::size_t;

    Set() : tree_(new tree_type{}) {}

    Set(std::initializer_list<value_type> const &items) {
      for (value_type i : items) insert(i);
    }

    Set(const Set &v) {}

    Set(Set && v) noexcept {}

    ~Set() {
      delete tree_;
      tree_ = nullptr;
    }

    // methods

    iterator begin() noexcept { return iterator(); }

    const_iterator begin() const noexcept { return const_iterator(); }

    iterator end() noexcept { return iterator(); }

    const_iterator end() const noexcept { return const_iterator(); }
  }

 private:
  tree_type *tree_;
};
}  // namespace s21

#endif  // CPP2_SRC_S21_SET_H_