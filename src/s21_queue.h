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

    private:

        struct Node {
            value_type value;
            Node *prev;
            Node *next;

            explicit Node(const_reference value) : value(value), prev(nullptr), next(nullptr) {}
        };
    };
}

#endif  // CPP2_SRC_S21_QUEUE_H_