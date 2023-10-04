#ifndef CPP2_SRC_TREE_H_
#define CPP2_SRC_TREE_H_

namespace s21 {
  /**
  класс описывающий узел бинарного дерева
  */
  template <typename T, typename V>
  class Node {
    public:
    T key;            // значение ключа
    Node<T,V>* left;  // указатель на левый узел
    Node<T,V>* right; // указатель на правый узел
    Node<T,V>* top;   // указатель на родителя

    public:
    // КОнструктор для создания узла со значением ключа
    Node(const T& key) : key(key), left(nullptr), right(nullptr), top(nullptr) {}
    Node(T& key) : key(key), left(nullptr), right(nullptr), top(nullptr) {}
  }; // end class Node

  // класс бинарного дерева
  template <typename T, typename V>
  class Tree {
    public:
    // КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ
    Tree();     // конструктор по умолчанию - пустое дерево
    Tree(const Tree& copy); // rконструктор копирования
    ~Tree(); // деструктор (удаляет узлы дерева и выставляет указатель на корень - null)
    
    // методы для работы с деревом
    
    Node<T, V>* Insert(T key);        // вставка узла в соответсвующее место по ключу
    Node<T, V>* Insert(Node<T, V>* node, T key, Node<T, V>* parent); // вспомогательный метод для вставки узла
    void ClearTree(Node<T, V>* node);   // полностью очищает поддерево от переданново узла
    Node<T, V>* CopyTree(Node<T, V>* node); // полное копирование дерева


    // Параметр - указатель на корень дерева
    Node<T, V>* root;                 // указатель на корень дерева

  };
  /**
   * КОНСТРУКТОР ПО УМОЛЧАНИЮ
   * создает пустое дерево, где указатель на корень - null,
  */
  template <typename T, typename V>
  Tree<T, V>::Tree() : root(nullptr) {
  }

  /**
   * КОНСТРУКТОР ЕОПИРОВАНИЯ ДЕРЕВА
  */
  template <typename T, typename V>
  Tree<T, V>::Tree(const Tree& copy) : root(CopyTree(copy.root)){
  }

  /**
   * ДЕСТРУКТОР
   * Удаляются узлы дерева и значение указателя на корень дерева (root)
   * выставляется в null
  */
  template <typename T, typename V>
  Tree<T, V>::~Tree() {
    ClearTree(root);
    root = nullptr;
  }

  /**
   * Два метода для вставки узла в дерево
  */
template <typename T, typename V>
Node<T, V>* Tree<T, V>::Insert(T key) {
  root = Insert(root, key, nullptr);
  return root;
}

template <typename T, typename V>
Node<T, V>* Tree<T, V>::Insert(Node<T, V>* node, T key, Node<T, V>* parent) {
  // если дерево пустое, то создаем узел
  if (node == nullptr) {
    node = new Node<T, V>(key);
    node->top = parent;
  } else { // если дерево не пустое то рекурсивно идем по нему в нужное место
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
    return newNode;
  }
  
};

#endif  // CPP2_SRC_TREE_H_