#ifndef CPP2_S21_CONTAINERS_1_MASTER_VECTOR_H
#define CPP2_S21_CONTAINERS_1_MASTER_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <limits>

#include "stdexcept"

namespace s21 {

template <typename T>
class Vector {
 public:
  // attributes
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = value_type *;
  using const_iterator = const value_type *;
  using size_type = std::size_t;

  Vector() : vSize(0U), vCapacity(0U), vArr(nullptr) {}

  explicit Vector(size_type n)
      : vSize(n), vCapacity(n), vArr(n ? new value_type[n]() : nullptr) {}

  Vector(std::initializer_list<value_type> const &items)
      : vSize(items.size()), vCapacity(items.size()) {
    vArr = new value_type[items.size()]();
    size_t i = 0;
    for (auto it = items.begin(); it != items.end(); ++it) {
      at(i) = *it;
      ++i;
    }
  }

  Vector(const Vector &v)
      : vSize(v.vSize),
        vCapacity(v.vCapacity),
        vArr(new value_type[v.vSize]()) {
    CopyEntryVector(v);
  }

  Vector(Vector &&v) noexcept
      : vSize(v.vSize), vCapacity(v.vCapacity), vArr(v.vArr) {
    v.vSize = 0;
    v.vCapacity = 0;
    v.vArr = nullptr;
  }

  ~Vector() { clear(); }

  // methods

  /*
  Replaces the contents of the container.
   */
  Vector<T> &operator=(const Vector<T> &v) {
    if (this != &v) {
      CleanVectorArr();
      vSize = v.vSize;
      vCapacity = v.vCapacity;
      vArr = new value_type[vSize]();
      CopyEntryVector(v);
    }
    return *this;
  }

  Vector<T> &operator=(Vector &&v) noexcept {
    CleanVectorArr();
    vSize = v.vSize;
    vCapacity = v.vCapacity;
    vArr = v.vArr;
    v.vSize = 0;
    v.vCapacity = 0;
    v.vArr = nullptr;
    return *this;
  }

  /*
  Returns a reference to the element at specified location pos, with bounds
  checking. If pos is not within the range of the container, an exception of
  type std::out_of_range is thrown.
  */
  reference at(size_type pos) {
    if (pos >= size()) throw std::out_of_range("Element is out of vector!");
    return vArr[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= vSize) throw std::out_of_range("Element is out of vector!");
    return vArr[pos];
  }

  /*
  Returns a reference to the element at specified location pos. No bounds
  checking is performed.
  */
  reference operator[](size_type pos) { return vArr[pos]; }

  const_reference operator[](size_type pos) const { return vArr[pos]; }

  /*
  Returns a reference to the first element in the container.
  Calling front on an empty container causes undefined behavior.
   */
  reference front() { return vArr[0]; }

  const_reference front() const { return vArr[0]; }

  /*
  Returns a reference to the last element in the container.
  Calling back on an empty container causes undefined behavior.
   */
  reference back() { return vArr[vSize - 1]; }

  const_reference back() const { return vArr[vSize - 1]; }

  /*
  Returns pointer to the underlying array serving as element storage.
   */
  iterator data() { return vArr; }

  const_iterator data() const { return vArr; }

  /*
  Returns an iterator to the first element of the vector.
  If the vector is empty, the returned iterator will be equal to end()
   */
  iterator begin() noexcept { return vArr; }

  const_iterator begin() const noexcept { return vArr; }

  /*
  Returns an iterator to the element following the last element of the vector.
  This element acts as a placeholder; attempting to access it results in
  undefined behavior.
   */
  iterator end() noexcept { return vArr + vSize; }

  const_iterator end() const noexcept { return vArr + vSize; }

  /*
  Checks if the container has no elements, i.e. whether begin() == end().
   */
  bool empty() const noexcept { return begin() == end(); }

  /*
  Returns the number of elements in the container,
  */
  size_type size() const noexcept { return vSize; }

  /*
  Returns the maximum number of elements the container is able to hold due to
  system or library implementation limitations, i.e. std::distance(begin(),
  end()) for the largest container.
   */
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  /*
  Increase the capacity of the vector (the total number of elements that the
  vector can hold without requiring reallocation) to a value that's greater or
  equal to new_cap. If new_cap is greater than the current capacity(), new
  storage is allocated, otherwise the function does nothing.
   */
  void reserve(size_type size) {
    if (size > vCapacity) {
      auto new_data = new value_type[size]();

      for (size_type i = 0; i < vSize; ++i) {
        new_data[i] = std::move(vArr[i]);
      }

      CleanVectorArr();
      vArr = new_data;
      vCapacity = size;
    }
  }

  /*
  Returns the number of elements that the container has currently allocated
  space for.
  */
  size_type capacity() const noexcept { return vCapacity; }

  /*
  Requests the removal of unused capacity.
  It is a non-binding request to reduce capacity() to lSize().
  If after the operation the new lSize() is greater than old capacity() a
  reallocation takes place, in which case all iterators (including the end()
  iterator) and all references to the elements are invalidated. If no
  reallocation occurs, no iterators or references are invalidated.
  */
  void shrink_to_fit() {
    if (vCapacity > vSize) {
      auto newData = new value_type[vSize]();

      for (size_type i = 0; i < vSize; ++i) {
        newData[i] = std::move(vArr[i]);
      }

      CleanVectorArr();
      vArr = newData;
      vCapacity = vSize;
    }
  }

  /*
  Erases all elements from the container. After this call, lSize() returns zero.
  Invalidates any references, pointers, or iterators referring to contained
  elements. Any past-the-end iterators are also invalidated. Leaves the
  capacity() of the vector unchanged (note: the standard's restriction on the
  changes to capacity is in the specification of vector::reserve, see
   */
  void clear() noexcept {
    CleanVectorArr();
    vArr = nullptr;
    vSize = 0;
  }

  /*
  Inserts elements at the specified location in the container before pos.
  If after the operation the new lSize() is greater than old capacity() a
  reallocation takes place, in which case all iterators (including the end()
  iterator) and all references to the elements are invalidated. Otherwise, only
  the iterators and references before the insertion point remain valid.
   */
  iterator insert(iterator pos, const_reference value) {
    size_type index = 0;
    if (vSize != 0) {
      index = pos - begin();  // when vSize = 0, begin() can be ub
    }

    if (vCapacity == vSize) {
      if (vCapacity == 0) {
        reserve(1);
      } else {
        reserve(vCapacity * 2);
      }
    }
    ++vSize;
    for (size_type i = vSize - 1; i > index; --i) {
      at(i) = std::move(at(i - 1));
    }
    at(index) = value;

    return begin() + index;
  }

  /*
  Erases the specified elements from the container at pos.
   */
  iterator erase(const_iterator pos) {
    size_type index = 0;
    if (vSize != 0) {
      index = pos - begin();  // when vSize = 0, begin() can be ub
    }
    for (size_type i = index; i < vSize - 1; ++i) {
      at(i) = std::move(at(i + 1));
    }
    --vSize;
    return begin() + index;
  }

  /*
  Appends the given element value to the end of the container.
  If after the operation the new lSize() is greater than old capacity() a
  reallocation takes place, in which case all iterators (including the end()
  iterator) and all references to the elements are invalidated. Otherwise only
  the end() iterator is invalidated.
   */
  void push_back(const_reference value) {
    if (vCapacity == vSize) {
      if (vCapacity == 0) {
        reserve(1);
      } else {
        reserve(vCapacity * 2);
      }
    }
    ++vSize;
    at(vSize - 1) = value;
  }

  /*
  Removes the last element of the container.
  Calling pop_back on an empty container results in undefined behavior.
  Iterators (including the end() iterator) and references to the last element
  are invalidated.
   */
  void pop_back() {
    vArr[vSize - 1].~value_type();
    --vSize;
  }

  /*
  Exchanges the contents and capacity of the container with those of others.
  Does not invoke any move, copy, or swap operations on individual elements. All
  iterators and references remain valid. The end() iterator is invalidated.
   */
  void swap(Vector &other) {
    std::swap(vArr, other.vArr);
    std::swap(vSize, other.vSize);
    std::swap(vCapacity, other.vCapacity);
  }

 private:
  size_type vSize;
  size_type vCapacity;
  T *vArr;

  // support
  void CopyEntryVector(const Vector<T> &from_matrix) {
    for (size_t i = 0; i < from_matrix.vSize; ++i) {
      at(i) = from_matrix.at(i);
    }
  }

  void CleanVectorArr() { delete[] vArr; }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_MASTER_VECTOR_H
