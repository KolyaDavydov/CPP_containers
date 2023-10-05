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

TEST(QueueInitializer, DoubleQueue) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Queue<double> que{1.0, 2.0, 3.0, 4.0, 5.0};
    std::queue<double> std_que(std_lst);

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(std_que.size(), 5U);
}

TEST(QueueInitializer, StringQueue) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Queue<std::string> que{"1", "2", "3", "4", "5"};
    std::queue<std::string> std_que(std_lst);

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(std_que.size(), 5U);
}

TEST(QueueCopyConstructor, IntCopyConstructor) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Queue<int> original{1, 2, 3, 4, 5};
    std::queue<int> std_original(std_lst);

    s21::Queue<int> copy(original);
    std::queue<int> std_copy(std_original);

    EXPECT_EQ(std_original.size(), std_copy.size());
    EXPECT_EQ(original.size(), 5);
    EXPECT_EQ(original.size(), copy.size());
}

TEST(QueueCopyConstructor, DoubleCopyConstructor) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Queue<double> original{1.0, 2.0, 3.0, 4.0, 5.0};
    std::queue<double> std_original(std_lst);

    s21::Queue<double> copy(original);
    std::queue<double> std_copy(std_original);

    EXPECT_EQ(std_original.size(), std_copy.size());
    EXPECT_EQ(original.size(), 5);
    EXPECT_EQ(original.size(), copy.size());
}

TEST(QueueCopyConstructor, StringCopyConstructor) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Queue<std::string> original{"1", "2", "3", "4", "5"};
    std::queue<std::string> std_original(std_lst);

    s21::Queue<std::string> copy(original);
    std::queue<std::string> std_copy(std_original);

    EXPECT_EQ(std_original.size(), std_copy.size());
    EXPECT_EQ(original.size(), 5);
    EXPECT_EQ(original.size(), copy.size());
}

TEST(FromVectorToQueue, Constructor) {
    std::vector<int> std_lst{1, 2, 3, 4, 5};

    s21::Queue<int, std::vector<int>> que{1, 2, 3, 4, 5};
    std::queue<int, std::vector<int>> std_que(std_lst);

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(std_que.size(), 5U);
}

TEST(FromVectorToQueue, CopyConstructor) {
    std::vector<int> std_lst{1, 2, 3, 4, 5};

    s21::Queue<int, std::vector<int>> original{1, 2, 3, 4, 5};
    std::queue<int, std::vector<int>> std_original(std_lst);

    s21::Queue<int, std::vector<int>> copy(original);
    std::queue<int, std::vector<int>> std_copy(std_original);

    EXPECT_EQ(std_original.size(), std_copy.size());
    EXPECT_EQ(original.size(), 5);
    EXPECT_EQ(original.size(), copy.size());
}



