#ifndef CPP2_SRC_S21_QUEUE_H_
#define CPP2_SRC_S21_QUEUE_H_

#include "stdexcept"

namespace s21 {

    template<typename T>
    class Queue {

    public:
        // attributes
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = std::size_t;

        Queue(): qSize(0) {
            carbineNode = new Node(value_type());
            carbineNode->next = carbineNode;
            carbineNode->prev = carbineNode;
        }

        Queue(std::initializer_list<value_type> const &items) : Queue() {
            for (const_reference item: items) {
                push_back(item);
            }
        }

        Queue(const Queue &q) : Queue() {
            for (const_reference item: q) {
                push_back(item);
            }
        }

        Queue(Queue &&q) noexcept: Queue() {
            qSize = q.qSize;
            q.qSize = 0;
            std::swap(carbineNode, q.carbineNode);
        }

        /*
        Replaces the contents of the container.
        */
        void clear() {
            Node *currentNode = carbineNode->next; // первая нода
            while (currentNode != carbineNode) {
                Node *temp = currentNode;
                currentNode = currentNode->next;
                delete temp;
            }
            carbineNode->next = carbineNode;
            carbineNode->prev = carbineNode;
            qSize = 0;
        }

        Queue<T> &operator=(const Queue<T> &q) {
            if (this != &q) {
                clear();
                for (const_reference item: q) {
                    push_back(item);
                }
            }
            return *this;
        }

        Queue<T> &operator=(Queue<T> &&q) noexcept {
            clear();
            qSize = q.qSize;
            q.lSize = 0;
            std::swap(carbineNode, q.carbineNode);
            return *this;
        }

        ~Queue() {
            clear();
            delete carbineNode;
        }

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
        Checks if the container has no elements.
        */
        bool empty() const noexcept {
            return carbineNode->next == carbineNode;
        }

        /*
        Returns the number of elements in the container.
        */
        size_type size() const noexcept {
            return qSize;
        }


    private:
        struct Node {
            value_type value;
            Node *prev;
            Node *next;

            explicit Node(const_reference value) : value(value), prev(nullptr), next(nullptr) {}
        };

        Node *carbineNode;
        size_type qSize;
    };
}

#endif  // CPP2_SRC_S21_QUEUE_H_