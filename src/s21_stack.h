#ifndef CPP2_SRC_S21_STACK_H_
#define CPP2_SRC_S21_STACK_H_

#include "stdexcept"
#include <initializer_list>
#include "s21_list.h"

namespace s21 {

    template<typename T, typename Container = s21::List<T>>
    class Stack {

    public:
        // attributes
        using value_type = typename Container::value_type;
        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;
        using size_type = typename Container::size_type;

        Stack() : container() {
        }

        Stack(std::initializer_list<value_type> const &items) : container(items) {
        }

        Stack(const Stack &q) : container(q.container) {
        }

        Stack(Stack &&q) noexcept {
            container = std::move(q.container);
        }


        Stack<T, Container> &operator=(const Stack &q) {
            if (this != &q) {
                container = q.container;
            }
            return *this;
        }

        Stack<T, Container> &operator=(Stack &&q) noexcept {
            //  if (this != &q) { //  по сути эта проверка бессмысленна, перемещение самого себя приведет к уб и мы не должны от этого защищать
            container = std::move(q.container);
            //  }
            return *this;
        }

        ~Stack() = default;

        /*
        Returns a reference to the last element in the container.
        Calling back on an empty container causes undefined behavior.
         */
        reference top() {
            return container.back();
        }

        /*
        Checks if the container has no elements.
        */
        bool empty() const noexcept {
            return container.empty();
        }

        /*
        Returns the number of elements in the container.
        */
        size_type size() const noexcept {
            return container.size();
        }

        void push(const_reference value) {
            container.push_back(value);
        }

        void pop() {
            container.pop_back();
        }

        /*
        Exchanges the contents of the container with those of others. Does not invoke any move, copy, or swap operations
        on individual elements.
         */
        void swap(Stack &other) {
            container.swap(other.container);
        }

    private:
        Container container;
    };
}

#endif  // CPP2_SRC_S21_STACK_H_