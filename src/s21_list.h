#ifndef CPP2_S21_CONTAINERS_1_MASTER_S21_LIST_H
#define CPP2_S21_CONTAINERS_1_MASTER_S21_LIST_H

#include <initializer_list>
#include <limits>
#include "stdexcept"

namespace s21 {

    template<typename T>
    class List {

    public:
        // attributes
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = std::size_t;

        List() : lSize(0) {
            carbineNode = new Node(value_type());
            carbineNode->next = carbineNode;
            carbineNode->prev = carbineNode;
        }

        explicit List(size_type n) : List() {
            for (size_t i = 0; i < n; ++i) {
                push_back(T());
            }
        }

        List(std::initializer_list<value_type> const &items) : List() {
            for (const_reference item: items) {
                push_back(item);
            }
        }

        List(const List &v) : List() {
            for (const_reference item: v) {
                push_back(item);
            }
        }

        List(List &&v) noexcept: List() {
            lSize = v.lSize;
            v.lSize = 0;
            std::swap(carbineNode, v.carbineNode);
        }

        /*
        Replaces the contents of the container.
        */
        List<T> &operator=(const List<T> &v) {
            if (this != &v) {
                clear();
                //   carbineNode->prev = carbineNode;
                //   carbineNode->next = carbineNode;
                for (const_reference item: v) {
                    push_back(item);
                }
            }
            return *this;
        }

        List<T> &operator=(List<T> &&v) noexcept {
            clear();
            lSize = v.lSize;
            v.lSize = 0;
            std::swap(carbineNode, v.carbineNode);
            return *this;
        }

        ~List() {
            clear();
            delete carbineNode;
        }


    private:
        struct Node {
            value_type value;
            Node *prev;
            Node *next;

            explicit Node(const_reference value) : value(value), prev(nullptr), next(nullptr) {}
        };

        Node *carbineNode;
        size_type lSize;

        class ListIterator {
        public:
            explicit ListIterator(Node *node, Node *carbineNode) : currentNode(node), carbineNode(carbineNode) {}

            ListIterator &operator++() {
                currentNode = currentNode->next;
                return *this;
            }

            ListIterator &operator--() {
                if (currentNode) {
                    currentNode = currentNode->prev;
                }
                return *this;
            }

            reference operator*() const {
                if (currentNode == carbineNode) {
                    throw std::runtime_error("Node is out of list (carbonNode)");
                }
                return currentNode->value;
            }

            bool operator==(const ListIterator &other) const {
                return currentNode == other.currentNode;
            }

            bool operator!=(const ListIterator &other) const {
                return currentNode != other.currentNode;;
            }

            Node *getCurrentNode() {
                return currentNode;
            }

        private:
            Node *currentNode;
            Node *carbineNode;
        };


        class ListCostIterator {
        public:
            explicit ListCostIterator(Node *node, Node *carbineNode) : currentNode(node), carbineNode(carbineNode) {}

            ListCostIterator &operator++() {
                currentNode = currentNode->next;
                return *this;
            }

            ListCostIterator &operator--() {
                currentNode = currentNode->prev;
                return *this;
            }

            const_reference operator*() const {
                if (currentNode == carbineNode) {
                    throw std::runtime_error("Node is out of list (carbonNode)");
                }
                return currentNode->value;
            }

            bool operator==(const ListCostIterator &other) const {
                return currentNode == other.currentNode;
            }

            bool operator!=(const ListCostIterator &other) const {
                return currentNode != other.currentNode;;
            }

            Node *getCurrentNode() {
                return currentNode;
            }

        private:
            Node *currentNode;
            Node *carbineNode;
        };


    public:
        using iterator = ListIterator;
        using const_iterator = ListCostIterator;

        /*
        Returns a reference to the first element in the container.
        Calling front on an empty container causes undefined behavior.
         */
        reference front() {
            return carbineNode->next->value;
        }

        const_reference front() const {
            return carbineNode->next->value;
        }

        /*
        Returns a reference to the last element in the container.
        Calling back on an empty container causes undefined behavior.
         */
        reference back() {
            return carbineNode->prev->value;
        }

        const_reference back() const {
            return carbineNode->prev->value;
        }

        /*
        Returns the maximum number of elements the container is able to hold due to system or library implementation
        limitations, i.e. std::distance(begin(), end()) for the largest container.
        */
        size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
        }

        /*
        Returns the number of elements in the container, i.e. std::distance(begin(), end())
        */
        size_type size() const noexcept {

            return lSize;
        }

        /*
        Returns an iterator to the first element of the vector.
        If the vector is empty, the returned iterator will be equal to end()
         */
        iterator begin() noexcept {
            return iterator(carbineNode->next, carbineNode);

        }

        const_iterator begin() const noexcept {
            return const_iterator(carbineNode->next, carbineNode);
        }

        /*
        Returns an iterator to the element following the last element of the vector.
        This element acts as a placeholder; attempting to access it results in undefined behavior.
         */
        iterator end() noexcept {
            return iterator(carbineNode, carbineNode);
        }

        const_iterator end() const noexcept {
            return const_iterator(carbineNode, carbineNode);
        }

        /*
        Checks if the container has no elements, i.e. whether begin() == end().
        */
        bool empty() const noexcept {
            return carbineNode->next == carbineNode;
        }

        // modifiers
        void clear() {
            Node *currentNode = carbineNode->next; // первая нода
            while (currentNode != carbineNode) {
                Node *temp = currentNode;
                currentNode = currentNode->next;
                delete temp;
            }
            carbineNode->next = carbineNode;
            carbineNode->prev = carbineNode;
            lSize = 0;
        }

        /*
        Inserts elements at the specified location in the container before pos.
         */
        iterator insert(iterator pos, const_reference value) {
            Node *insertedNode = new Node(value);

            insertedNode->next = pos.getCurrentNode();
            insertedNode->prev = pos.getCurrentNode()->prev;
            pos.getCurrentNode()->prev->next = insertedNode;
            pos.getCurrentNode()->prev = insertedNode;
            ++lSize;
            return iterator(insertedNode, carbineNode);
        }

        /*
         Erases the specified elements from the container. Removes the element at pos
         */
        iterator erase(iterator pos) {
            if (pos.getCurrentNode() == carbineNode) {
                // в оригининале это уб с ликом памяти и неправильным результатом size()
                --lSize;
                return pos;
            }
            Node *tempNode = pos.getCurrentNode();
            Node *nextIter = tempNode->next;
            tempNode->prev->next = tempNode->next;
            tempNode->next->prev = tempNode->prev;
            delete tempNode;

            if (nextIter == carbineNode) {
                carbineNode->prev = carbineNode;
                carbineNode->next = carbineNode;
            }
            --lSize;
            return iterator(nextIter, carbineNode);
        }

        void push_back(const_reference value) {
            insert(end(), value);
            /*
            Node *newNode = new Node(value);
            newNode->prev = carbineNode->prev; //Мы указываем предыдущий узел нового узла как узел, который был последним узлом в списке до добавления нового элемента. Таким образом, у нового узла будет тот же предыдущий узел, что и у последнего элемента списка.
            newNode->next = carbineNode; // Мы указываем следующий узел нового узла как "круговой" узел (фейковый узел), чтобы завершить кольцевую структуру списка.
            carbineNode->prev->next = newNode; // Мы обновляем следующий узел у предыдущего узла (последнего узла в списке до добавления нового элемента) так, чтобы он указывал на новый узел. Таким образом, "старый" последний узел будет указывать на новый узел как следующий.
            carbineNode->prev = newNode; // Мы обновляем предыдущий узел у "кругового" узла так, чтобы он указывал на новый узел. Таким образом, "круговой" узел будет указывать на новый узел как предыдущий.
            ++lSize;
             */
        }

        void push_front(const_reference value) {
            insert(begin(), value);
            /*
            Node *newNode = new Node(value);
            newNode->next = carbineNode->next;
            newNode->prev = carbineNode;
            carbineNode->next->prev = newNode;
            carbineNode->next = newNode;
            ++lSize;
             */
        }

        void pop_back() {
            iterator pos = --end();
            erase(pos);
            /*
            if (carbineNode->prev != carbineNode) {
                Node *temmNode = carbineNode->prev;
                carbineNode->prev = temmNode->prev;
                carbineNode->prev->next = carbineNode;
                delete temmNode;
                --lSize;
            }
             */
        }

        void pop_front() {
            erase(begin());
            /*
            if (carbineNode->next != carbineNode) {
                Node *temmNode = carbineNode->next;
                carbineNode->next = temmNode->next;
                carbineNode->next->prev = carbineNode;
                delete temmNode;
                --lSize;
            }
             */
        }

        /*
        Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations
        on individual elements.
         */
        void swap(List<T> &other) {
            std::swap(carbineNode, other.carbineNode);
            std::swap(lSize, other.lSize);
        }

        /*
        The function does nothing if other refers to the same object as *this.

        Otherwise, merges other into *this. Both lists should be sorted. No elements are copied, and the container
        other becomes empty after the merge. This operation is stable: for equivalent elements in the two lists, the
        elements from *this always precede the elements from other, and the order of equivalent elements of *this and
        other does not change.

        No iterators or references to become invalidated. The pointers and references to the elements moved from *this,
        as well as the iterators referring to these elements, will refer to the same elements of *this, instead of
        others.
         */
        void merge(List<T> &other) {
            if (this == &other) {
                return;
            }
            lSize += other.lSize;

            iterator it1 = begin();
            iterator it2 = other.begin();

            while (it1 != end() && it2 != other.end()) {
                if (*it2 < *it1) {
                    insert(it1, *it2);
                    ++it2;
                } else {
                    ++it1;
                }
            }

            while (it2 != other.end()) {
                push_back(*it2);
                ++it2;
            }

            other.clear();
        }

        /*
        Reverses the order of the elements in the container. No references or iterators become invalidated
         */
        void reverse() noexcept {
            if (lSize < 2) {
                return;
            }
            Node *node = carbineNode->next;
            while (node != carbineNode) {
                std::swap(node->next, node->prev);
                node = node->prev;
            }
            std::swap(carbineNode->prev, carbineNode->next);
        }

        /*
        Removes all consecutive duplicate elements from the container. Only the first element in each group of equal
         elements is left
         */
        void unique() {
            if (lSize < 2) {
                return;
            }
            iterator it = begin();
            iterator next = it;
            ++next;

            while (next != end()) {
                if (*it == *next) {
                    next = erase(next);
                } else {
                    ++it;
                    ++next;
                }
            }
        }

        /*
        Sorts the elements and preserves the order of equivalent elements. No references or iterators become invalidated
         */
        void sort() {
            if (lSize < 2) {
                return;
            }

            List<T> left;
            List<T> right;

            size_type middle = lSize / 2;
            auto it = begin();
            for (size_type i = 0; i < middle; ++i) {
                left.push_back(*it);
                ++it;
            }
            while (it != end()) {
                right.push_back(*it);
                ++it;
            }

            // Рекурсивная сортировка обеих половин
            left.sort();
            right.sort();

            // Слияние двух отсортированных половин
            clear(); // Очищаем текущий список
            *this = left;
            merge(right);
        }

        /*
         Transfers elements from one list to another.
        No elements are copied or moved, only the internal pointers of the list nodes are re-pointed. No iterators or
        references to become invalidated, the iterators to moved elements remain valid, but now refer into *this, not
         into others.

        Transfers all elements from other into *this. The elements are inserted before the element pointed to by pos.
        The container other becomes empty after the operation.
         */
        void splice(iterator pos, List<T> &other) {
            if (other.empty()) {
                return;
            }
            iterator otherIt = other.begin();
            while (otherIt != other.end()) {
                pos = insert(pos, *otherIt);
                ++pos;
                ++otherIt;
            }
            other.clear();
        }
    };
}

#endif //CPP2_S21_CONTAINERS_1_MASTER_S21_LIST_H