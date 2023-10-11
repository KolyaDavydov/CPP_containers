#include <gtest/gtest.h>
#include "deque"
#include "stack"
#include "list"

#include "../s21_stack.h"

using MyTypes = testing::Types<int, double, std::list<int>, std::string>;

template<typename T>
class StackTest : public testing::Test {
protected:
    s21::Stack<T> que;
    std::stack<T> std_que;
};

TYPED_TEST_SUITE(StackTest, MyTypes);
TYPED_TEST(StackTest, DefaultConstructor) {
    s21::Stack<TypeParam> que;
    std::stack<TypeParam> std_que;

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(que.empty(), std_que.empty());
    EXPECT_EQ(std_que.size(), 0U);
}

TEST(StackInitializer, IntStack) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Stack<int> que{1, 2, 3, 4, 5};
    std::stack<int> std_que(std_lst);

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(que.empty(), std_que.empty());
    EXPECT_EQ(std_que.size(), 5U);
}

TEST(StackInitializer, DoubleStack) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Stack<double> que{1.0, 2.0, 3.0, 4.0, 5.0};
    std::stack<double> std_que(std_lst);

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(que.empty(), std_que.empty());
    EXPECT_EQ(std_que.size(), 5U);
}

TEST(StackInitializer, StringStack) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Stack<std::string> que{"1", "2", "3", "4", "5"};
    std::stack<std::string> std_que(std_lst);

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(que.empty(), std_que.empty());
    EXPECT_EQ(std_que.size(), 5U);
}

TEST(StackCopyConstructor, IntCopyConstructor) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Stack<int> original{1, 2, 3, 4, 5};
    std::stack<int> std_original(std_lst);

    s21::Stack<int> copy(original);
    std::stack<int> std_copy(std_original);

    EXPECT_EQ(std_original.size(), std_copy.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), copy.size());
}

TEST(StackCopyConstructor, DoubleCopyConstructor) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Stack<double> original{1.0, 2.0, 3.0, 4.0, 5.0};
    std::stack<double> std_original(std_lst);

    s21::Stack<double> copy(original);
    std::stack<double> std_copy(std_original);

    EXPECT_EQ(std_original.size(), std_copy.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), copy.size());
}

TEST(StackCopyConstructor, StringCopyConstructor) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Stack<std::string> original{"1", "2", "3", "4", "5"};
    std::stack<std::string> std_original(std_lst);

    s21::Stack<std::string> copy(original);
    std::stack<std::string> std_copy(std_original);

    EXPECT_EQ(std_original.size(), std_copy.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), copy.size());
}

TEST(FromVectorToStack, Constructor) {
    std::vector<int> std_lst{1, 2, 3, 4, 5};

    s21::Stack<int, std::vector<int>> que{1, 2, 3, 4, 5};
    std::stack<int, std::vector<int>> std_que(std_lst);

    EXPECT_EQ(que.size(), std_que.size());
    EXPECT_EQ(std_que.size(), 5U);
}

TEST(FromVectorToStack, CopyConstructor) {
    std::vector<int> std_lst{1, 2, 3, 4, 5};

    s21::Stack<int, std::vector<int>> original{1, 2, 3, 4, 5};
    std::stack<int, std::vector<int>> std_original(std_lst);

    s21::Stack<int, std::vector<int>> copy(original);
    std::stack<int, std::vector<int>> std_copy(std_original);

    EXPECT_EQ(std_original.size(), std_copy.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), copy.size());
}

TEST(StackMoveConstructor, IntConstructor) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Stack<int> original{1, 2, 3, 4, 5};
    std::stack<int> std_original(std_lst);

    s21::Stack<int> moved(std::move(original));
    std::stack<int> std_moved(std::move(std_original));

    EXPECT_EQ(std_original.size(), original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(moved.size(), std_moved.size());
    EXPECT_EQ(moved.size(), 5U);
}

TEST(StackMoveConstructor, DoubleConstructor) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Stack<double> original{1.0, 2.0, 3.0, 4.0, 5.0};
    std::stack<double> std_original(std_lst);

    s21::Stack<double> moved(std::move(original));
    std::stack<double> std_moved(std::move(std_original));

    EXPECT_EQ(std_original.size(), original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(moved.size(), std_moved.size());
    EXPECT_EQ(moved.size(), 5U);
}

TEST(StackMoveConstructor, StringConstructor) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Stack<std::string> original{"1", "2", "3", "4", "5"};
    std::stack<std::string> std_original(std_lst);

    s21::Stack<std::string> moved(std::move(original));
    std::stack<std::string> std_moved(std::move(std_original));

    EXPECT_EQ(std_original.size(), original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(moved.size(), std_moved.size());
    EXPECT_EQ(moved.size(), 5U);
}

TEST(StackAssignCopy, IntAssign) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Stack<int> original{1, 2, 3, 4, 5};
    std::stack<int> std_original(std_lst);

    s21::Stack<int> que;
    std::stack<int> std_que;

    que = original;
    std_que = std_original;

    EXPECT_EQ(std_original.size(), std_que.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), que.size());
    EXPECT_EQ(original.size(), std_original.size());
}

TEST(StackAssignCopy, DoubleAssign) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Stack<double> original{1.0, 2.0, 3.0, 4.0, 5.0};
    std::stack<double> std_original(std_lst);

    s21::Stack<double> que;
    std::stack<double> std_que;

    que = original;
    std_que = std_original;

    EXPECT_EQ(std_original.size(), std_que.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), que.size());
    EXPECT_EQ(original.size(), std_original.size());
}

TEST(StackAssignCopy, StringAssign) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Stack<std::string> original{"1", "2", "3", "4", "5"};
    std::stack<std::string> std_original(std_lst);

    s21::Stack<std::string> que;
    std::stack<std::string> std_que;

    que = original;
    std_que = std_original;

    EXPECT_EQ(std_original.size(), std_que.size());
    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), que.size());
    EXPECT_EQ(original.size(), std_original.size());
}

TEST(StackAssignMove, IntMove) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Stack<int> original{1, 2, 3, 4, 5};
    std::stack<int> std_original(std_lst);

    s21::Stack<int> que;
    std::stack<int> std_que;

    que = std::move(original);
    std_que = std::move(std_original);

    EXPECT_EQ(std_original.size(), std_original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(std_que.size(), que.size());
    EXPECT_EQ(que.size(), 5U);
}

TEST(StackAssignMove, DoubleMove) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Stack<double> original{1.0, 2.0, 3.0, 4.0, 5.0};
    std::stack<double> std_original(std_lst);

    s21::Stack<double> que;
    std::stack<double> std_que;

    que = std::move(original);
    std_que = std::move(std_original);

    EXPECT_EQ(std_original.size(), std_original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(std_que.size(), que.size());
    EXPECT_EQ(que.size(), 5U);
}

TEST(StackAssignMove, StringMove) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Stack<std::string> original{"1", "2", "3", "4", "5"};
    std::stack<std::string> std_original(std_lst);

    s21::Stack<std::string> que;
    std::stack<std::string> std_que;

    que = std::move(original);
    std_que = std::move(std_original);

    EXPECT_EQ(std_original.size(), std_original.size());
    EXPECT_EQ(original.size(), 0U);
    EXPECT_EQ(std_que.size(), que.size());
    EXPECT_EQ(que.size(), 5U);
}


TEST(StackSelfAssignCopyConstructor, IntAssign) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Stack<int> original{1, 2, 3, 4, 5};
    std::stack<int> std_original(std_lst);

    original = original;
    std_original = std_original;

    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), std_original.size());
}

TEST(StackSelfAssignCopyConstructor, DoubleAssign) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Stack<double> original{1.0, 2.0, 3.0, 4.0, 5.0};
    std::stack<double> std_original(std_lst);

    original = original;
    std_original = std_original;

    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), std_original.size());
}

TEST(StackSelfAssignCopyConstructor, StringAssign) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Stack<std::string> original{"1", "2", "3", "4", "5"};
    std::stack<std::string> std_original(std_lst);

    s21::Stack<std::string> que;
    std::stack<std::string> std_que;

    original = original;
    std_original = std_original;

    EXPECT_EQ(original.size(), 5U);
    EXPECT_EQ(original.size(), std_original.size());
}

// swap
TEST(StackSwap, IntSwap) {
    std::deque<int> std_lst1{1, 2, 3, 4, 5};
    std::deque<int> std_lst2{6, 7, 8, 9, 10};

    s21::Stack<int> original1{1, 2, 3, 4, 5};
    s21::Stack<int> original2{6, 7, 8, 9, 10};
    std::stack<int> std_original1(std_lst1);
    std::stack<int> std_original2(std_lst2);

    original1.swap(original2);
    std_original1.swap(std_original2);

    EXPECT_EQ(original1.top(), 10);
    EXPECT_EQ(original1.top(), std_original1.top());
    EXPECT_EQ(original2.top(), 5);
    EXPECT_EQ(original2.top(), std_original2.top());
}

TEST(StackSwap, DoubleSwap) {
    std::deque<double> std_lst1{1.0, 2.0, 3.0, 4.0, 5.0};
    std::deque<double> std_lst2{6.0, 7.0, 8.0, 9.0, 10.0};

    s21::Stack<double> original1{1.0, 2.0, 3.0, 4.0, 5.0};
    s21::Stack<double> original2{6.0, 7.0, 8.0, 9.0, 10.0};
    std::stack<double> std_original1(std_lst1);
    std::stack<double> std_original2(std_lst2);

    original1.swap(original2);
    std_original1.swap(std_original2);

    EXPECT_EQ(original1.top(), 10.0);
    EXPECT_EQ(original1.top(), std_original1.top());
    EXPECT_EQ(original2.top(), 5.0);
    EXPECT_EQ(original2.top(), std_original2.top());
}

TEST(StackSwap, StringSwap) {
    std::deque<std::string> std_lst1{"1", "2", "3", "4", "5"};
    std::deque<std::string> std_lst2{"6", "7", "8", "9", "10"};

    s21::Stack<std::string> original1{"1", "2", "3", "4", "5"};
    s21::Stack<std::string> original2{"6", "7", "8", "9", "10"};
    std::stack<std::string> std_original1(std_lst1);
    std::stack<std::string> std_original2(std_lst2);

    original1.swap(original2);
    std_original1.swap(std_original2);

    EXPECT_EQ(original1.top(), "10");
    EXPECT_EQ(original1.top(), std_original1.top());
    EXPECT_EQ(original2.top(), "5");
    EXPECT_EQ(original2.top(), std_original2.top());
}

// front, back, push, pop

TEST(StackMethods, IntStack) {
    std::deque<int> std_lst{1, 2, 3, 4, 5};

    s21::Stack<int> que{1, 2, 3, 4, 5};
    std::stack<int> std_que(std_lst);

    EXPECT_EQ(que.top(), std_que.top());


    EXPECT_EQ(que.top(), 5);
    EXPECT_EQ(std_que.size(), 5U);


    que.push(6);
    std_que.push(6);
    EXPECT_EQ(que.top(), std_que.top());
    EXPECT_EQ(que.top(), 6);
    EXPECT_EQ(std_que.size(), 6U);


    que.pop();
    std_que.pop();
    EXPECT_EQ(que.size(), 5U);
  EXPECT_EQ(que.top(), std_que.top());
    EXPECT_EQ(que.top(), 5);

}

TEST(StackMethods, DoubleStack) {
    std::deque<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

    s21::Stack<double> que{1.0, 2.0, 3.0, 4.0, 5.0};
    std::stack<double> std_que(std_lst);

    EXPECT_EQ(que.top(), std_que.top());
    EXPECT_EQ(que.top(), 5.0);

    que.push(6.0);
    std_que.push(6.0);
    EXPECT_EQ(que.top(), std_que.top());
    EXPECT_EQ(que.top(), 6.0);
    EXPECT_EQ(que.size(), 6U);

    que.pop();
    std_que.pop();
    EXPECT_EQ(que.top(), std_que.top());
    EXPECT_EQ(que.top(), 5.0);
    EXPECT_EQ(que.size(), 5U);
}

TEST(StackMethods, StringStack) {
    std::deque<std::string> std_lst{"1", "2", "3", "4", "5"};

    s21::Stack<std::string> que{"1", "2", "3", "4", "5"};
    std::stack<std::string> std_que(std_lst);

    EXPECT_EQ(que.top(), std_que.top());
    EXPECT_EQ(que.top(), "5");

    que.push("6");
    std_que.push("6");
    EXPECT_EQ(que.top(), std_que.top());
    EXPECT_EQ(que.top(), "6");
    EXPECT_EQ(que.size(), 6U);

    que.pop();
    std_que.pop();
    EXPECT_EQ(que.top(), std_que.top());
    EXPECT_EQ(que.top(), "5");
    EXPECT_EQ(que.size(), 5U);
}
