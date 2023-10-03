#ifndef CPP2_SRC_TREE_H_
#define CPP2_SRC_TREE_H_

namespace s21 {
  /**
  класс описывающий узел бинарного дерева
  */
  template <typename T, typename V>
  class Node {
    T key;            // значение ключа
    Node<T,V>* left;  // указатель на левый узел
    Node<T,V>* right; // указатель на правый узел
    Node<T,V>* top;   // указатель на родителя

    // КОнструктор для создания узла со значением ключа
    Node(const T& key) : key(k), left(nullptr), right(nullptr), top(nullptr) {}
  }; // end class Node

  // класс бинарного дерева
  template <typename T, typename V>
  class Tree {
    public:
    // КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ
    Tree();     // по умолчанию - пустое дерево
    ~Tree(); // деструктор (адаляет узлы дерева и выставляет указатель на корень - null)
    
    // методы для работы с деревом
    Node<T, V>* InsertRootNode(T key); // вставляет в пустое дерево корневой узел и возвращает указатель на корень
    Node<T, V>* InsertNode(Node<T, V>* node, T key, Node<T, V>* top); // вставляет узел в дерево
    void ClearTree(Node<T, V>* node);   // полностью очищает поддерево от переданново узла

    // Параметр - указатель на корень дерева
    Node<T, V>* root; // указатель на корень дерева
  };
  /**
   * КОНСТРУКТОР ПО УМОЛЧАНИЮ
   * создает пустое дерево, где указатель на корень - null
  */
  template <typename T, typename V>
  Tree<T, V>::Tree() : root(nullptr) {}

  /**
   * ДЕСТРУКТОР
   * Удаляются узлы дерева и значение указателя на корень дерева (root)
   * выставляется в null
  */
  template <typename T, typename V>
  Tree<T, V>::~Tree() {
    ClearNode(root);
    root = nullptr;
  }

  /**
   * вставялет в пустое дерево корневой узел
   * возвращаемое значение - указатель на корневой узел
  */
  template <typename T, typename V>
  Node<T, V>* Tree<T, V>::InsertRootNode(T key) {
    root = InsertNode(root, key, nullptr);
    return root;
  }

  /**
   * вставялет узел в дерево согласно условию упорядочиванию:
   * если ключ меньше то идет рекурсивно влево и наоборот
   * возвращаемое значение - указатель на вставляемый узел
  */
  template <typename T, typename V>
  Node<T, V>* Tree<T, V>::InsertNode(Node<T, V>* node, T key, Node<T, V>* top) {
    if (node != nullptr) {
      node = new Node<T, V>(key);
      node->top = top;
      return node;
    }
    if(kye < node->key) {
      node->left = InsertNode(node->left, key, node);
    } else if (key > node->key) {
      node->right = InsertNode(node->right, key, node);
    }
    return node;
  }

  /**
   * полностью очищает поддерево начиная от передаваемого узла
  */
  template <typename T, typename V>
  void Tree<T, V>::ClearTree(Node<T, V>* node) {
    if (node != nullptr) {
      ClearTree(node->left);
      ClearTree(node->right);
      delete node;
    }
  }
};

#endif  // CPP2_SRC_TREE_H_