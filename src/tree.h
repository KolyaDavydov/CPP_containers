#ifndef CPP2_SRC_TREE_H_
#define CPP2_SRC_TREE_H_

#include <iostream>
#include <limits>  // для std::numeric_limits

namespace s21 {

/**
 * Здесь три класса:
 * - class Node
 * - class Tree
 * - class Iterator
 */

// ========== КЛАСС УЗЛА ============== //

template <typename T, typename V>
class Node {
 public:
  T key;              // значение ключа
  V val;              // Згачение значения
  Node<T, V>* left;   // указатель на левый узел
  Node<T, V>* right;  // указатель на правый узел
  Node<T, V>* top;    // указатель на родителя

  bool is_min;  // если true то это узел с самым минимальным значением
  bool is_max;  // если true то это узел с самым максимальным значением

  // КОнструкторы для создания узла со значением ключа
  Node(const T& key)
      : key(key),
        left(nullptr),
        right(nullptr),
        top(nullptr),
        is_min(false),
        is_max(false) {}
  Node(T& key)
      : key(key),
        left(nullptr),
        right(nullptr),
        top(nullptr),
        is_min(false),
        is_max(false) {}
};  // end class Node

// ========== КЛАСС ПРОСТОГО БИНАРНОГО ДЕРЕВА ============== //

// Здесь объявляем класс и его параметры, функции и т.д.
// описание самих функций идет ниже класса
template <typename T, typename V>
class Tree {
 public:
  // КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ
  Tree();  // конструктор по умолчанию - пустое дерево
  Tree(const Tree& copy);  // конструктор копирования
  ~Tree();  // деструктор (удаляет узлы дерева и выставляет
            // указатель на корень - null)

  // Перезагрузка оператора присваивания для перемещающегося объекта
  Tree<T, V>& operator=(Tree&& other);

  // ОСНОВНЫЕ ПУБЛИЧНЫЕ МЕТОДЫ ДЛЯ РАБОТЫ С ДЕРЕВОМ
  Node<T, V>* Insert(T key);  // вставка узла в соответсвующее место по ключу

  // полностью очищает поддерево от переданново узла
  void ClearTree(Node<T, V>* node);

  // полное копирование дерева передать указатель на корень копируемого дерева
  // !!! не копирует остальные приватные параметры (T min, T max, Size)
  Node<T, V>* CopyTree(Node<T, V>* node);
  // метод для поиска узла по переданному ключу
  Node<T, V>* Search(T key);

  // методы для удаления узла дерева по переданному ключу
  void Remove(T key);
  // смена содержимого контейнера на содержимое другого
  void Swap(Tree<T, V>& other);
  size_t MaxSize();  // возвращает максимальный размер контейнера (весьма
                     // неоднозначная функция)

 private:
  // ПАРАМЕТРЫ КЛАССА ДЕРЕВА делаем приватными для безопасности
  Node<T, V>* root;  // указатель на корень дерева
  T min;  // для хранения максимального значения ключа дерева
  T max;  // для хранения минимального значения
  size_t size;  // размер дерева

 private:  // приватные вспомогательные методы, которыу учавствуют только в этом
           // классе
  // вспомогательный метод для вставки узла
  Node<T, V>* Insert(Node<T, V>* node, T key, Node<T, V>* parent);
  // вспомогательный метод для поиска узла по ключу
  Node<T, V>* Search(T key, Node<T, V>* node);

  // вспомогательные методы для удаления узла
  Node<T, V>* FindMin(Node<T, V>* node);
  Node<T, V>* RemoveMin(Node<T, V>* node);
  Node<T, V>* Remove(Node<T, V>* node, T key);

 public:
  // геттеры и сеттеры для работы с приватными параметрами
  size_t GetSize() { return this->size; }
  Node<T, V>* GetRoot() { return this->root; }
  void SetRoot(Node<T, V>* root) { this->root = root; }
  T GetMax() { return this->max; }
  T GetMin() { return this->min; }
};  // end class Tree
/**
 * КОНСТРУКТОР ПО УМОЛЧАНИЮ
 * создает пустое дерево, где указатель на корень - null,
 */
template <typename T, typename V>
Tree<T, V>::Tree() : root(nullptr), min(), max(), size(0) {}

/**
 * КОНСТРУКТОР КОПИРОВАНИЯ ДЕРЕВА
 */
template <typename T, typename V>
Tree<T, V>::Tree(const Tree& copy) : root(CopyTree(copy.root)) {
  this->size = copy.size;

  this->max = copy.max;
  this->min = copy.min;
}

/**
 * ДЕСТРУКТОР
 * Удаляются узлы дерева и значение указателя на корень дерева (root)
 * выставляется в null
 */
template <typename T, typename V>
Tree<T, V>::~Tree() {
  ClearTree(root);
  // root = nullptr;
}

// оператор присваивания переносом
template <typename T, typename V>
Tree<T, V>& Tree<T, V>::operator=(Tree&& other) {
  if (this != other) {
    ClearTree(root);
    root = exchange(other.root, nullptr);
  }
  return *this;
}

/**
 * Два метода для вставки узла в дерево
 */
template <typename T, typename V>
Node<T, V>* Tree<T, V>::Insert(T key) {
  root = Insert(root, key, nullptr);

  if (key < this->min || this->size == 0) {
    this->min = key;
  }
  if (key > this->max || this->size == 0) {
    this->max = key;
  }
  this->size++;
  return root;
}

template <typename T, typename V>
Node<T, V>* Tree<T, V>::Insert(Node<T, V>* node, T key, Node<T, V>* parent) {
  // если дерево пустое, то создаем узел
  if (node == nullptr) {
    node = new Node<T, V>(key);
    node->top = parent;
    // следующие три if для того что бы вписать в занчение узла
    // краевой он или нет, для дальнейшего итеррирования без сеги
    if (this->size < 1) {
      node->is_max = true;
      node->is_min = true;
    }
    if (this->size >= 1 && node->key < this->min) {
      node->is_min = true;
      node->top->is_min = false;
    }
    if (this->size >= 1 && node->key > this->max) {
      node->is_max = true;
      node->top->is_max = false;
    }

  } else {  // если дерево не пустое то рекурсивно идем по нему в нужное место
    if (key < node->key) {
      node->left = Insert(node->left, key, node);
    } else if (key > node->key) {
      node->right = Insert(node->right, key, node);
    }
  }

  return node;
}

/**
 * полностью очищает дерево
 * принимает указатель на корневой узел
 */
template <typename T, typename V>
void Tree<T, V>::ClearTree(Node<T, V>* node) {
  if (node != nullptr) {
    ClearTree(node->left);
    ClearTree(node->right);
    delete node;
  }
  root = nullptr;
  max = {};
  min = {};
  size = 0;
}

/**
 * метод копирования всего дерева
 * принимает указатель на корневой узел копируемого дерева
 * !!! перед копированием нужно инициализировать пустое дерево
 * возвращаемое значение - указатель на корневой узел нового дерева
 */
template <typename T, typename V>
Node<T, V>* Tree<T, V>::CopyTree(Node<T, V>* node) {
  if (node == nullptr) return nullptr;
  Node<T, V>* newNode = new Node<T, V>(node->key);
  newNode->left = CopyTree(node->left);
  newNode->right = CopyTree(node->right);
  newNode->top = node->top;
  // this->size++;
  newNode->is_max = node->is_max;
  newNode->is_min = node->is_min;

  return newNode;
}

/**
 * Два метода для поиска значения ключа в дереве
 * возвращаемое значение на указатель узла этого ключа
 */
template <typename T, typename V>
Node<T, V>* Tree<T, V>::Search(T key) {
  return Search(key, root);
}

template <typename T, typename V>
Node<T, V>* Tree<T, V>::Search(T key, Node<T, V>* node) {
  if (node == nullptr || node->key == key) {
    return node;
  }
  if (key < node->key) {
    return Search(key, node->left);
  } else {
    return Search(key, node->right);
  }
}

// Методы для удаления узла дерева
template <typename T, typename V>
void Tree<T, V>::Remove(T key) {
  Node<T, V>* n = Search(key);
  if (key == this->min) {
    // std::cout << "Проверка Размер: " << this->min << std::endl;
    if (size > 1) {
      if (n->top != nullptr) this->min = n->top->key;
      if (n->top == nullptr) this->min = n->right->key;
    }
  }
  if (key == this->max) {
    if (size > 1) {
      if (n->top != nullptr) this->max = n->top->key;
      if (n->top == nullptr) this->max = n->left->key;
    }
  }
  root = Remove(root, key);
}

template <typename T, typename V>
Node<T, V>* Tree<T, V>::FindMin(Node<T, V>* node) {
  if (!node->left) return node;
  return FindMin(node->left);
}
template <typename T, typename V>
Node<T, V>* Tree<T, V>::RemoveMin(Node<T, V>* node) {
  if (!node->left) return node->right;
  node->left = RemoveMin(node->left);
  return node;
}
template <typename T, typename V>
Node<T, V>* Tree<T, V>::Remove(Node<T, V>* node, T key) {
  if (!node) return nullptr;
  if (key < node->key) {
    node->left = Remove(node->left, key);
  } else if (key > node->key) {
    node->right = Remove(node->right, key);
  } else {
    Node<T, V>* left = node->left;
    Node<T, V>* right = node->right;
    delete node;
    if (!right) return left;
    if (!left) return right;
    // std::cout << "Размерasd: " << left->key << std::endl;
    Node<T, V>* min = FindMin(right);
    min->right = RemoveMin(right);
    min->left = left;
    min->left->top = right;
    this->size--;
    // min->top = node->top;

    return min;
  }
  this->size--;
  return node;
}

// смена содержимого контейнера на содержимое другого
template <typename T, typename V>
void Tree<T, V>::Swap(Tree<T, V>& other) {
  std::swap(root, other.root);
  std::swap(size, other.size);
  std::swap(min, other.min);
  std::swap(max, other.max);
}

/* Расчет максимального размера контейнера
 * - Размер size_t должен совпадать с размером указателя для любой
 * платформы. Указатель должен быть в состоянии адресовать любой байт в
 * памяти, а size_t хранить размер любого (в т.ч. занимающего всю память)
 * объекта. Таким образом максимальное значение size_t - это максимальное
 * количество байт памяти. Это значение мы получаем при помощи
 * std::numeric_limits<size_t>::max();
 *
 * - GCC ограничивает объекты размером в половину адресного пространства.
 * Поэтому полученное в число делим на 2.
 *
 * - Чтобы определить максимальное количество элементов в контейнере, делим
 * число, на размер одного узла, т.е. sizeof(Node)
 * Функция выводит число но это число больше оригинала, может что то нужно
 * исправить...
 */
template <typename T, typename V>
size_t Tree<T, V>::MaxSize() {
  size_t max_size =
      std::numeric_limits<size_t>::max() / 2 / sizeof(Node<T, V>*);
  return max_size;
}

// ========== КЛАСС ИТЕРАТОР ========== //
template <typename T, typename V>
class Iterator {
 public:
  // содержит два параметра:
  Node<T, V>* node_;  // указатель на текущий узел дерева
  Node<T, V>* root_;  // указатель на корневой узел дерева

  // единственный конструктор,
  // принимает указатель на узел (node) и указатель на корень (root)
  // и передает их в параметры класса
  Iterator(Node<T, V>* node, Node<T, V>* root) : node_(node), root_(root) {}

  // перезагружаем операторы:
  // получение указателя на значение ключа, на узел которого указывает итератор
  T& operator*() const { return node_->key; }

  // Перезагрузка операторов инкремента и декремента:
  // Сделаем постфиксную и префиксную перезагрузку:
  // https://learn.microsoft.com/ru-ru/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-170

  // перезагрузка префиксного оператора инкремента
  Iterator& operator++() {
    if (node_ != nullptr && node_->is_max != true) {
      if (node_->right != nullptr) {
        node_ = node_->right;
        while (node_->left != nullptr) {
          node_ = node_->left;
        }
      } else {
        Node<T, V>* parent = node_->top;
        while (parent != nullptr && node_ == parent->right) {
          node_ = parent;
          parent = parent->top;
        }
        node_ = parent;
      }
      return *this;
    }

    return *this;
  }

  // перезагрузка постфиксного оператора инкремента
  Iterator operator++(int) {
    Iterator tmp_incr = *this;
    ++(*this);
    return tmp_incr;
  }

  // перезагрузка префиксного оператора декремента
  Iterator& operator--() {
    if (node_ != nullptr && node_->is_min != true) {
      if (node_->left != nullptr) {
        node_ = node_->left;
        while (node_->right != nullptr) {
          node_ = node_->right;
        }
      } else {
        Node<T, V>* parent = node_->top;
        while (parent != nullptr && node_ == parent->left) {
          node_ = parent;
          parent = parent->top;
        }
        node_ = parent;
      }
      return *this;
    }
    return *this;
  }

  // перезагрузка постфиксного оператора декремента
  Iterator operator--(int) {
    Iterator tmp_incr = *this;
    --(*this);
    return tmp_incr;
  }

  // перезагрузка оператора '=='
  // Два итератора равны, если они указывают на один и тот же элемент.
  bool operator==(const Iterator& other) const { return node_ == other.node_; }

  // перезагрузка оператора '!='
  bool operator!=(const Iterator& other) const { return node_ != other.node_; }
};  // end class ITERATOR

};  // end namespace s21

#endif  // CPP2_SRC_TREE_H_