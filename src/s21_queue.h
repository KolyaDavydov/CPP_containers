#ifndef CPP2_SRC_S21_QUEUE_H_
#define CPP2_SRC_S21_QUEUE_H_

#include "stdexcept"
#include <initializer_list>
#include "s21_list.h"

namespace s21 {

    template<typename T, typename Container = s21::List<T>>
    class Queue {

    public:
        // attributes
        using value_type = typename Container::value_type;
        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;
        using size_type = typename Container::size_type;

        Queue() : container() {            ;
        }

        Queue(std::initializer_list<value_type> const &items) :  container(items) {
        }

        Queue(const Queue &q) : container(q.container) {

        }

        Queue(Queue &&q) noexcept  {
            container = std::move(q.container);
        }


        Queue<T, Container> &operator=(const Queue &q) {
            if (this != &q) {
                container = q.container;
            }
            return *this;
        }

        Queue<T, Container> &operator=(Queue &&q) noexcept {
          //  if (this != &q) { //  по сути эта проверка бессмысленна, перемещение самого себя приведет к уб и мы не должны от этого защищать
                container = q.container;
          //  }
            return *this;
        }

        ~Queue() = default;

        /*
            Returns a reference to the first element in the container.
            Calling front on an empty container causes undefined behavior.
             */
        reference front() {
            return container.front();
        }

        /*
        Returns a reference to the last element in the container.
        Calling back on an empty container causes undefined behavior.
         */
        reference back() {
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
            container.pop_front();
        }

        /*
        Exchanges the contents of the container with those of others. Does not invoke any move, copy, or swap operations
        on individual elements.
         */
        void swap(Queue &other) {
            container.swap(other.container);
        }


    private:
        Container container;
    };
}

#endif  // CPP2_SRC_S21_QUEUE_H_