#include <gtest/gtest.h>
#include "deque"
#include "queue"
#include "list"

#include "s21_queue.h"

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
    EXPECT_EQ(que.empty(), std_que.empty());
    EXPECT_EQ(std_que.size(), 0U);
}

TEST(QueueInitializer, IntQueue) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Queue<int> que{1, 2, 3, 4, 5};
    std::queue<int> std_que(std_lst);

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(que.empty(), std_que.empty());
    EXPECT_EQ(std_que.size(), 5U);
}

TEST(QueueInitializer, DoubleQueue) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Queue<double> que{1.0, 2.0, 3.0, 4.0, 5.0};
    std::queue<double> std_que(std_lst);

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(que.empty(), std_que.empty());
    EXPECT_EQ(std_que.size(), 5U);
}

TEST(QueueInitializer, StringQueue) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Queue<std::string> que{"1", "2", "3", "4", "5"};
    std::queue<std::string> std_que(std_lst);

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(que.empty(), std_que.empty());
    EXPECT_EQ(std_que.size(), 5U);
}

TEST(QueueCopyConstructor, IntCopyConstructor) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Queue<int> original{1, 2, 3, 4, 5};
    std::queue<int> std_original(std_lst);

    s21::Queue<int> copy(original);
    std::queue<int> std_copy(std_original);

    EXPECT_EQ(std_original.size(), std_copy.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), copy.size());
}

TEST(QueueCopyConstructor, DoubleCopyConstructor) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Queue<double> original{1.0, 2.0, 3.0, 4.0, 5.0};
    std::queue<double> std_original(std_lst);

    s21::Queue<double> copy(original);
    std::queue<double> std_copy(std_original);

    EXPECT_EQ(std_original.size(), std_copy.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), copy.size());
}

TEST(QueueCopyConstructor, StringCopyConstructor) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Queue<std::string> original{"1", "2", "3", "4", "5"};
    std::queue<std::string> std_original(std_lst);

    s21::Queue<std::string> copy(original);
    std::queue<std::string> std_copy(std_original);

    EXPECT_EQ(std_original.size(), std_copy.size());
    EXPECT_EQ(original.size(), 5U);
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
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), copy.size());
}

TEST(QueueMoveConstructor, IntConstructor) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Queue<int> original{1, 2, 3, 4, 5};
    std::queue<int> std_original(std_lst);

    s21::Queue<int> moved(std::move(original));
    std::queue<int> std_moved(std::move(std_original));

    EXPECT_EQ(std_original.size(), original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(moved.size(), std_moved.size());
    EXPECT_EQ(moved.size(), 5U);
}

TEST(QueueMoveConstructor, DoubleConstructor) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Queue<double> original{1.0, 2.0, 3.0, 4.0, 5.0};
    std::queue<double> std_original(std_lst);

    s21::Queue<double> moved(std::move(original));
    std::queue<double> std_moved(std::move(std_original));

    EXPECT_EQ(std_original.size(), original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(moved.size(), std_moved.size());
    EXPECT_EQ(moved.size(), 5U);
}

TEST(QueueMoveConstructor, StringConstructor) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Queue<std::string> original{"1", "2", "3", "4", "5"};
    std::queue<std::string> std_original(std_lst);

    s21::Queue<std::string> moved(std::move(original));
    std::queue<std::string> std_moved(std::move(std_original));

    EXPECT_EQ(std_original.size(), original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(moved.size(), std_moved.size());
    EXPECT_EQ(moved.size(), 5U);
}

TEST(QueueAssignCopy, IntAssign) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Queue<int> original{1, 2, 3, 4, 5};
    std::queue<int> std_original(std_lst);

    s21::Queue<int> que;
    std::queue<int> std_que;

    que = original;
    std_que = std_original;

    EXPECT_EQ(std_original.size(), std_que.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), que.size());
    EXPECT_EQ(original.size(), std_original.size());
}

TEST(QueueAssignCopy, DoubleAssign) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Queue<double> original{1.0, 2.0, 3.0, 4.0, 5.0};
    std::queue<double> std_original(std_lst);

    s21::Queue<double> que;
    std::queue<double> std_que;

    que = original;
    std_que = std_original;

    EXPECT_EQ(std_original.size(), std_que.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), que.size());
    EXPECT_EQ(original.size(), std_original.size());
}

TEST(QueueAssignCopy, StringAssign) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Queue<std::string> original{"1", "2", "3", "4", "5"};
    std::queue<std::string> std_original(std_lst);

    s21::Queue<std::string> que;
    std::queue<std::string> std_que;

    que = original;
    std_que = std_original;

    EXPECT_EQ(std_original.size(), std_que.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), que.size());
    EXPECT_EQ(original.size(), std_original.size());
}

TEST(QueueAssignMove, IntMove) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Queue<int> original{1, 2, 3, 4, 5};
    std::queue<int> std_original(std_lst);

    s21::Queue<int> que;
    std::queue<int> std_que;

    que = std::move(original);
    std_que = std::move(std_original);

    EXPECT_EQ(std_original.size(), std_original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(std_que.size(), que.size());
    EXPECT_EQ(que.size(), 5U);
}

TEST(QueueAssignMove, DoubleMove) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Queue<double> original{1.0, 2.0, 3.0, 4.0, 5.0};
    std::queue<double> std_original(std_lst);

    s21::Queue<double> que;
    std::queue<double> std_que;

    que = std::move(original);
    std_que = std::move(std_original);

    EXPECT_EQ(std_original.size(), std_original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(std_que.size(), que.size());
    EXPECT_EQ(que.size(), 5U);
}

TEST(QueueAssignMove, StringMove) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Queue<std::string> original{"1", "2", "3", "4", "5"};
    std::queue<std::string> std_original(std_lst);

    s21::Queue<std::string> que;
    std::queue<std::string> std_que;

    que = std::move(original);
    std_que = std::move(std_original);

    EXPECT_EQ(std_original.size(), std_original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(std_que.size(), que.size());
    EXPECT_EQ(que.size(), 5U);
}


TEST(QueueSelfAssignCopyConstructor, IntAssign) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Queue<int> original{1, 2, 3, 4, 5};
    std::queue<int> std_original(std_lst);

    original = original;
    std_original = std_original;

    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), std_original.size());
}

TEST(QueueSelfAssignCopyConstructor, DoubleAssign) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Queue<double> original{1.0, 2.0, 3.0, 4.0, 5.0};
    std::queue<double> std_original(std_lst);

    original = original;
    std_original = std_original;

    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), std_original.size());
}

TEST(QueueSelfAssignCopyConstructor, StringAssign) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Queue<std::string> original{"1", "2", "3", "4", "5"};
    std::queue<std::string> std_original(std_lst);

    s21::Queue<std::string> que;
    std::queue<std::string> std_que;

    original = original;
    std_original = std_original;

    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), std_original.size());
}

// swap
TEST(QueueSwap, IntSwap) {
    std::deque<int> std_lst1{1, 2, 3, 4, 5};
    std::deque<int> std_lst2{6, 7, 8, 9, 10};

    s21::Queue<int> original1{1, 2, 3, 4, 5};
    s21::Queue<int> original2{6, 7, 8, 9, 10};
    std::queue<int> std_original1(std_lst1);
    std::queue<int> std_original2(std_lst2);

    original1.swap(original2);
    std_original1.swap(std_original2);

    EXPECT_EQ(original1.front(), 6);
    EXPECT_EQ(original1.front(), std_original1.front());
    EXPECT_EQ(original2.front(), 1);
    EXPECT_EQ(original2.front(), std_original2.front());
}

TEST(QueueSwap, DoubleSwap) {
    std::deque<double> std_lst1{1.0, 2.0, 3.0, 4.0, 5.0};
    std::deque<double> std_lst2{6.0, 7.0, 8.0, 9.0, 10.0};

    s21::Queue<double> original1{1.0, 2.0, 3.0, 4.0, 5.0};
    s21::Queue<double> original2{6.0, 7.0, 8.0, 9.0, 10.0};
    std::queue<double> std_original1(std_lst1);
    std::queue<double> std_original2(std_lst2);

    original1.swap(original2);
    std_original1.swap(std_original2);

    EXPECT_EQ(original1.front(), 6.0);
    EXPECT_EQ(original1.front(), std_original1.front());
    EXPECT_EQ(original2.front(), 1.0);
    EXPECT_EQ(original2.front(), std_original2.front());
}

TEST(QueueSwap, StringSwap) {
    std::deque<std::string> std_lst1{"1", "2", "3", "4", "5"};
    std::deque<std::string> std_lst2{"6", "7", "8", "9", "10"};

    s21::Queue<std::string> original1{"1", "2", "3", "4", "5"};
    s21::Queue<std::string> original2{"6", "7", "8", "9", "10"};
    std::queue<std::string> std_original1(std_lst1);
    std::queue<std::string> std_original2(std_lst2);

    original1.swap(original2);
    std_original1.swap(std_original2);

    EXPECT_EQ(original1.front(), "6");
    EXPECT_EQ(original1.front(), std_original1.front());
    EXPECT_EQ(original2.front(), "1");
    EXPECT_EQ(original2.front(), std_original2.front());
}

// front, back, push, pop

TEST(QueueMethods, IntQueue) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Queue<int> que{1, 2, 3, 4, 5};
    std::queue<int> std_que(std_lst);

    EXPECT_EQ(que.front(), std_que.front());
    EXPECT_EQ(que.front(), 1);
    EXPECT_EQ(que.back(), std_que.back());
    EXPECT_EQ(que.back(), 5);

    que.push(6);
    std_que.push(6);
    EXPECT_EQ(que.back(), std_que.back());
    EXPECT_EQ(que.back(), 6);
    EXPECT_EQ(que.size(), 6U);

    que.pop();
    std_que.pop();
    EXPECT_EQ(que.front(), std_que.front());
    EXPECT_EQ(que.front(), 2);
    EXPECT_EQ(que.size(), 5U);
}

TEST(QueueMethods, DoubleQueue) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Queue<double> que{1.0, 2.0, 3.0, 4.0, 5.0};
    std::queue<double> std_que(std_lst);

    EXPECT_EQ(que.front(), std_que.front());
    EXPECT_EQ(que.front(), 1.0);
    EXPECT_EQ(que.back(), std_que.back());
    EXPECT_EQ(que.back(), 5.0);

    que.push(6.0);
    std_que.push(6.0);
    EXPECT_EQ(que.back(), std_que.back());
    EXPECT_EQ(que.back(), 6.0);
    EXPECT_EQ(que.size(), 6U);

    que.pop();
    std_que.pop();
    EXPECT_EQ(que.front(), std_que.front());
    EXPECT_EQ(que.front(), 2.0);
    EXPECT_EQ(que.size(), 5U);
}

TEST(QueueMethods, StringQueue) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Queue<std::string> que{"1", "2", "3", "4", "5"};
    std::queue<std::string> std_que(std_lst);

    EXPECT_EQ(que.front(), std_que.front());
    EXPECT_EQ(que.front(), "1");
    EXPECT_EQ(que.back(), std_que.back());
    EXPECT_EQ(que.back(), "5");

    que.push("6");
    std_que.push("6");
    EXPECT_EQ(que.back(), std_que.back());
    EXPECT_EQ(que.back(), "6");
    EXPECT_EQ(que.size(), 6U);

    que.pop();
    std_que.pop();
    EXPECT_EQ(que.front(), std_que.front());
    EXPECT_EQ(que.front(), "2");
    EXPECT_EQ(que.size(), 5U);
}