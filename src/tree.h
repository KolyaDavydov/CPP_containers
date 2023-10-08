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

    bool extreme; // если true то это крайний узел (первый или последний)

    public:
    // КОнструктор для создания узла со значением ключа
    Node(const T& key) : key(key), left(nullptr), right(nullptr), top(nullptr), extreme(false) {}
    Node(T& key) : key(key), left(nullptr), right(nullptr), top(nullptr), extreme(false) {}
  }; // end class Node

  // класс бинарного дерева
  template <typename T, typename V>
  class Tree {
    public:

    class Iterator;
    // Внутрений класс итератор
    // class Iterator;

    // КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ
    Tree();     // конструктор по умолчанию - пустое дерево
    Tree(const Tree& copy); // rконструктор копирования
    ~Tree(); // деструктор (удаляет узлы дерева и выставляет указатель на корень - null)
    
    // Перезагрузка оператора присваивания для перемещающегося объекта
    Tree<T, V>& operator=(Tree&& other);
    // методы для работы с деревом
    
    Node<T, V>* Insert(T key);        // вставка узла в соответсвующее место по ключу
    Node<T, V>* Insert(Node<T, V>* node, T key, Node<T, V>* parent); // вспомогательный метод для вставки узла
    void ClearTree(Node<T, V>* node);   // полностью очищает поддерево от переданново узла
    Node<T, V>* CopyTree(Node<T, V>* node); // полное копирование дерева
    // два метода - поиск в дереве по переданому значения ключа
    Node<T, V>* Search(T key);          
    Node<T, V>* Search(T key, Node<T, V>* node);

    // Параметр - указатель на корень дерева
    Node<T, V>* root;                 // указатель на корень дерева
    T min;  // для хранения максимального значения ключа дерева
    T max;  // для хранения минимального значения

    int size;   // размер дерева
  };
  /**
   * КОНСТРУКТОР ПО УМОЛЧАНИЮ
   * создает пустое дерево, где указатель на корень - null,
  */
  template <typename T, typename V>
  Tree<T, V>::Tree() : root(nullptr), min(), max(), size(0) {
  }

  /**
   * КОНСТРУКТОР ЕОПИРОВАНИЯ ДЕРЕВА
  */
  template <typename T, typename V>
  Tree<T, V>::Tree(const Tree& copy) : root(CopyTree(copy.root)) {
      this->size = copy.size;
      if (size == 0) {
        this->max = copy.max;
        this->min = copy.min;        
      } else {
        this->max = copy.max;
        this->min = copy.min;
      }
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

  // оператор присваивания переносом
  template <typename T, typename V>
  Tree<T, V>& Tree<T, V>::operator=(Tree&& other) {
    if (this != other) {
      ClearTree(root);
      root = exchange(other.root, nullptr);
    }
    return * this;
  }

  /**
   * Два метода для вставки узла в дерево
  */
template <typename T, typename V>
Node<T, V>* Tree<T, V>::Insert(T key) {
  root = Insert(root, key, nullptr);
    
    
    if(key < this->min || this->size == 0) {
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
    if(this->size < 2) {
    node->extreme = true;
    }
    if(this->size > 1 && node->key < this->min) {
      node->extreme = true;
      node->top->extreme = false;
    }
    if(this->size > 1 && node->key > this->max) {
      node->extreme = true;
      node->top->extreme = false;
    }

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
  // max = {};
  // min = {};
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
    newNode->extreme = node->extreme;


    return newNode;
  }
  
    /**
   * Два метода для поиска значения ключа в дереве
  */
  template <typename T, typename V>
  Node<T, V>* Tree<T, V>::Search(T key){
    return Search(key, root);
  } 

  template <typename T, typename V>
  Node<T, V>* Tree<T, V>::Search(T key, Node<T, V>* node){
    if (node == nullptr || node->key == key) {
      return node;
    }
    if (key < node->key) {
      return Search(key, node->left);
    } else {
      return Search(key, node->right);
    }
  }

  // ВНУТРЕНИЙ КЛАСС ИТЕРАТОР
  template <typename T, typename V>
  class Iterator {
    public:
    // содержит два параметра:
    Node<T, V>* node_; // указатель на текущий узел дерева
    Node<T, V>* root_; // указатель на корневой узел дерева

    // единственный конструктор,
    // принимает указатель на узел (node) и указатель на корень (root)
    // и передает их в параметры класса
    Iterator(Node<T, V>* node, Node<T, V>* root) : node_(node), root_(root) {
    }


    // перезагружаем операторы:
    // получение указателя на значение ключа, на узел которого указывает итератор
    T& operator*() const {
      return node_->key;
    }

    // Перезагрузка операторов инкремента и декремента:
    // Сделаем постфиксную и префиксную перезагрузку: https://learn.microsoft.com/ru-ru/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-170

    // перезагрузка префиксного оператора инкремента
    // !!! Если доходит до конечного элемента, то вылетает сега - ПОДУМАТЬ
    Iterator& operator++() {
      if (node_ != nullptr && node_->extreme != true) {
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
    // !!! Если доходит до начального элемента, то вылетает сега - ПОДУМАТЬ
    Iterator& operator--() {
      if (node_ != nullptr && node_->extreme != true) {
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
    bool operator==(const Iterator& other) const {
      return node_ == other.node_;
    }

        // перезагрузка оператора '!='
    bool operator!=(const Iterator& other) const {
      return node_ != other.node_;
    }

  };

};

#endif  // CPP2_SRC_TREE_H_