#include <gtest/gtest.h>
#include "deque"
#include "queue"
#include "list"

#include "s21_queue.h"

#define s21_EPS 1e-7

using MyTypes = testing::Types<int, double, std::list<int>, std::string>;

template<typename T>
class QueueTest : public testing::Test {
protected:
    s21::Queue<T> que;
    std::queue<T> std_que;
};

TYPED_TEST_SUITE(QueueTest, MyTypes);
TYPED_TEST(QueueTest, DefaultConstructor) {
    s21::Queue<TypeParam> que;
    std::queue<TypeParam> std_que;

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(std_que.size(), 0U);
}

TEST(QueueInitializer, IntQueue) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Queue<int> que{1, 2, 3, 4, 5};
    std::queue<int> std_que(std_lst);

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(std_que.size(), 5U);
}


