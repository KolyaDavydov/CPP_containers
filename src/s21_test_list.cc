#include <gtest/gtest.h>

#include "list"
#include "s21_list.h"

#define s21_EPS 1e-7

using MyTypes = testing::Types<int, double, std::list<int>, std::string>;

template <typename T>
class ListTest : public testing::Test {
 protected:
  s21::List<T> lst;
  std::list<T> std_lst;
};

TYPED_TEST_SUITE(ListTest, MyTypes);
TYPED_TEST(ListTest, DefaultConstructor) {
  s21::List<TypeParam> lst;
  std::list<TypeParam> std_lst;

  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(std_lst.size(), 0U);
  EXPECT_EQ(lst.max_size(), std_lst.max_size());
}

TYPED_TEST(ListTest, ParamZeroConstructor) {
  size_t size = 0U;
  s21::List<TypeParam> lst(size);
  std::list<TypeParam> std_lst(size);

  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(std_lst.size(), size);
}

TYPED_TEST(ListTest, ParamSmallConstructor) {
  size_t size = 2U;
  s21::List<TypeParam> lst(size);
  std::list<TypeParam> std_lst(size);

  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(std_lst.size(), size);
  EXPECT_EQ(lst.max_size(), std_lst.max_size());
}

TYPED_TEST(ListTest, ParamBigConstructor) {
  size_t size = 100U;
  s21::List<TypeParam> lst(size);
  std::list<TypeParam> std_lst(size);

  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(std_lst.size(), size);
}

TEST(ListInitializer, IntList) {
  s21::List<int> lst{1, 2, 3, 4, 5};
  std::list<int> std_lst{1, 2, 3, 4, 5};

  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(std_lst.size(), 5U);
  EXPECT_EQ(lst.max_size(), std_lst.max_size());
}

TEST(ListInitializer, DoubleList) {
  s21::List<double> lst{1.0, 2.0, 3.0, 4.0, 5.0};
  std::list<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(std_lst.size(), 5U);
}

TEST(ListInitializer, StringList) {
  s21::List<std::string> lst{"1", "2", "3", "4", "5"};
  std::list<std::string> std_lst{"1", "2", "3", "4", "5"};

  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(std_lst.size(), 5U);
}

TYPED_TEST(ListTest, CopyConstructor) {
  size_t size = 5U;
  const s21::List<TypeParam> original(size);
  const s21::List<TypeParam> copy(original);

  const std::list<TypeParam> std_lst(size);
  const std::list<TypeParam> std_copy(std_lst);

  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_EQ(copy.size(), size);
  EXPECT_EQ(original.size(), copy.size());
}

TYPED_TEST(ListTest, MoveConstructor) {
  size_t size = 5U;
  s21::List<TypeParam> original(size);
  s21::List<TypeParam> moved(std::move(original));

  std::list<TypeParam> std_lst(size);
  std::list<TypeParam> std_moved(std::move(std_lst));

  EXPECT_EQ(moved.size(), std_moved.size());
  EXPECT_EQ(moved.size(), size);
  EXPECT_EQ(original.size(), std_lst.size());
  EXPECT_EQ(original.size(), 0U);

  EXPECT_EQ(std_moved.size(), size);
  EXPECT_EQ(std_lst.size(), 0U);
}

TYPED_TEST(ListTest, CopyAssign) {
  s21::List<TypeParam> original(5);
  const s21::List<TypeParam> copy(6);
  original = copy;

  std::list<TypeParam> std_lst(5);
  const std::list<TypeParam> std_copy(6);
  std_lst = std_copy;

  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(std_copy.size(), std_lst.size());
}

TYPED_TEST(ListTest, CopySelfAssign) {
  s21::List<TypeParam> original(5);
  original = original;

  std::list<TypeParam> std_vec(5);
  std_vec = std_vec;

  EXPECT_EQ(original.size(), std_vec.size());
  EXPECT_EQ(original.size(), 5U);
}

TYPED_TEST(ListTest, MoveAssign) {
  s21::List<TypeParam> original(5);
  s21::List<TypeParam> moved(6);
  original = std::move(moved);

  std::list<TypeParam> std_lst(5);
  std::list<TypeParam> std_moved(6);
  std_lst = std::move(std_moved);

  EXPECT_EQ(moved.size(), 0U);
  EXPECT_EQ(original.size(), 6U);

  EXPECT_EQ(std_moved.size(), 0U);
  EXPECT_EQ(std_lst.size(), 6U);
}

// TYPED_TEST(ListTest, MoveSelfAssign) {
//   // по сути это уб
//   s21::List<TypeParam> original(5);
//   original = std::move(original);

//   std::list<TypeParam> std_lst(5);
//   std_lst = std::move(std_lst);

//   EXPECT_EQ(original.size(), std_lst.size());
//   EXPECT_EQ(original.size(), 0U);
// }

// front, back, empty, beign, end
template <typename Iterator>
void check_begin_end_int_iterator(Iterator begin, Iterator end) {
  int entry = 0;
  for (auto it = begin; it != end; ++it) {
    EXPECT_EQ(*it, ++entry);
  }
}

TYPED_TEST(ListTest, EmptyIterator) {
  s21::List<TypeParam> lst;
  std::list<TypeParam> std_lst;

  EXPECT_TRUE(lst.begin() == lst.end());
  EXPECT_TRUE(std_lst.begin() == std_lst.end());
  EXPECT_TRUE(lst.empty());
  EXPECT_TRUE(std_lst.empty());
}

TEST(ListAccess, IntList) {
  s21::List<int> lst{1, 2, 3, 4, 5};
  std::list<int> std_lst{1, 2, 3, 4, 5};

  check_begin_end_int_iterator(lst.begin(), lst.end());
  check_begin_end_int_iterator(std_lst.begin(), std_lst.end());

  lst.front() = 30;
  std_lst.front() = 30;

  EXPECT_EQ(lst.front(), 30);
  EXPECT_EQ(std_lst.front(), 30);

  lst.back() = 40;
  std_lst.back() = 40;

  EXPECT_EQ(lst.back(), 40);
  EXPECT_EQ(std_lst.back(), 40);
}

template <typename Iterator>
void check_begin_end_double_iterator(Iterator begin, Iterator end) {
  int entry = 1.0;
  for (auto it = begin; it != end; ++it) {
    EXPECT_TRUE(std::abs(*it - entry) < s21_EPS);
    entry += 1.0;
  }
}

TEST(ListAccess, DoubleList) {
  s21::List<double> lst{1.0, 2.0, 3.0, 4.0, 5.0};
  std::list<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

  check_begin_end_double_iterator(lst.begin(), lst.end());
  check_begin_end_double_iterator(std_lst.begin(), std_lst.end());

  lst.front() = 30.0;
  std_lst.front() = 30.0;

  EXPECT_TRUE(lst.front() - 30 < s21_EPS);
  EXPECT_TRUE(std_lst.front() - 30 < s21_EPS);

  lst.back() = 40.0;
  std_lst.back() = 40.0;

  EXPECT_TRUE(lst.back() - 40 < s21_EPS);
  EXPECT_TRUE(std_lst.back() - 40 < s21_EPS);
}

template <typename Iterator>
void check_begin_end_string_iterator(Iterator begin, Iterator end) {
  int entry = 0;
  for (auto it = begin; it != end; ++it) {
    std::string strNumber = std::to_string(++entry);
    EXPECT_EQ(*it, strNumber);
  }
}

TEST(ListAccess, StringList) {
  s21::List<std::string> lst{"1", "2", "3", "4", "5"};
  std::list<std::string> std_lst{"1", "2", "3", "4", "5"};

  check_begin_end_string_iterator(lst.begin(), lst.end());
  check_begin_end_string_iterator(std_lst.begin(), std_lst.end());

  lst.front() = "30";
  std_lst.front() = "30";

  EXPECT_EQ(lst.front(), "30");
  EXPECT_EQ(std_lst.front(), "30");

  lst.back() = "40";
  std_lst.back() = "40";

  EXPECT_EQ(lst.back(), "40");
  EXPECT_EQ(std_lst.back(), "40");
}
// CONST!!!
TEST(ListAccess, ConstIntList) {
  const s21::List<int> lst{1, 2, 3, 4, 5};
  const std::list<int> std_lst{1, 2, 3, 4, 5};

  check_begin_end_int_iterator(lst.begin(), lst.end());
  check_begin_end_int_iterator(std_lst.begin(), std_lst.end());

  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(std_lst.front(), 1);

  EXPECT_EQ(lst.back(), 5);
  EXPECT_EQ(std_lst.back(), 5);
}

TEST(ListAccess, ConstDoubleList) {
  const s21::List<double> lst{1.0, 2.0, 3.0, 4.0, 5.0};
  const std::list<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

  check_begin_end_double_iterator(lst.begin(), lst.end());
  check_begin_end_double_iterator(std_lst.begin(), std_lst.end());

  EXPECT_TRUE(lst.front() - 1.0 < s21_EPS);
  EXPECT_TRUE(std_lst.front() - 1.0 < s21_EPS);

  EXPECT_TRUE(lst.back() - 5.0 < s21_EPS);
  EXPECT_TRUE(std_lst.back() - 5.0 < s21_EPS);
}

TEST(ListAccess, ConstStringList) {
  const s21::List<std::string> lst{"1", "2", "3", "4", "5"};
  const std::list<std::string> std_lst{"1", "2", "3", "4", "5"};

  check_begin_end_string_iterator(lst.begin(), lst.end());
  check_begin_end_string_iterator(std_lst.begin(), std_lst.end());

  EXPECT_EQ(lst.front(), "1");
  EXPECT_EQ(std_lst.front(), "1");

  EXPECT_EQ(lst.back(), "5");
  EXPECT_EQ(std_lst.back(), "5");
}

TEST(ListIterator, BadIter) {
  s21::List<std::string> lst{"1", "2", "3", "4", "5"};
  const s21::List<std::string> const_lst{"1", "2", "3", "4", "5"};

  s21::List<std::string>::iterator it = lst.end();
  s21::List<std::string>::const_iterator const_it = const_lst.end();

  EXPECT_THROW(*it, std::runtime_error);
  EXPECT_THROW(*const_it, std::runtime_error);
}

TEST(ListIterator, IterBack) {
  s21::List<int> lst{1, 2, 3, 4, 5};
  int expected = 5;
  for (auto it = lst.end(); it != lst.begin();) {
    --it;
    EXPECT_EQ(*it, expected--);
  }
}

TEST(ListIterator, IterForvard) {
  s21::List<std::string> lst{"1", "2", "3", "4", "5"};
  const s21::List<std::string> const_lst{"1", "2", "3", "4", "5"};

  s21::List<std::string>::iterator it = lst.begin();
  s21::List<std::string>::const_iterator const_it = const_lst.begin();

  for (int i = 0; i < 5;) {
    std::string strNumber = std::to_string(++i);
    EXPECT_EQ(*it, strNumber);
    EXPECT_EQ(*const_it, strNumber);
    ++it;
    ++const_it;
  }
}

// modifiers: insert, erase, push back, pop back
TEST(ListModifiers, IntList) {
  s21::List<int> lst{2, 3, 4, 5, 6};
  std::list<int> std_lst{2, 3, 4, 5, 6};

  lst.insert(lst.begin(), 1);
  lst.insert(lst.end(), 7);
  std_lst.insert(std_lst.begin(), 1);
  std_lst.insert(std_lst.end(), 7);
  ASSERT_EQ(lst.size(), 7U);
  ASSERT_EQ(lst.size(), std_lst.size());

  int test_count = 0;
  for (s21::List<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
    ASSERT_EQ(*it, ++test_count);
  }

  lst.erase(lst.begin());
  std_lst.erase(std_lst.begin());
  ASSERT_EQ(lst.size(), 6U);
  ASSERT_EQ(lst.size(), std_lst.size());
  int erase_count = 1;
  for (s21::List<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
    ASSERT_EQ(*it, ++erase_count);
  }

  lst.clear();
  std_lst.clear();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(lst.size(), 0U);
}

TEST(ListModifiers, DoubleList) {
  s21::List<double> lst{2.0, 3.0, 4.0, 5.0, 6.0};
  std::list<double> std_lst{2.0, 3.0, 4.0, 5.0, 6.0};

  lst.insert(lst.begin(), 1.0);
  lst.insert(lst.end(), 7.0);
  std_lst.insert(std_lst.begin(), 1.0);
  std_lst.insert(std_lst.end(), 7.0);
  ASSERT_EQ(lst.size(), 7U);
  ASSERT_EQ(lst.size(), std_lst.size());

  double test_count = 1.0;
  for (s21::List<double>::iterator it = lst.begin(); it != lst.end(); ++it) {
    ASSERT_TRUE(*it - test_count < s21_EPS);
    ++test_count;
  }

  lst.clear();
  std_lst.clear();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(lst.size(), 0U);
}

TEST(ListModifiers, StringList) {
  s21::List<std::string> lst{"2", "3", "4", "5", "6"};
  std::list<std::string> std_lst{"2", "3", "4", "5", "6"};

  lst.insert(lst.begin(), "1");
  lst.insert(lst.end(), "7");
  std_lst.insert(std_lst.begin(), "1");
  std_lst.insert(std_lst.end(), "7");
  ASSERT_EQ(lst.size(), 7U);
  ASSERT_EQ(lst.size(), std_lst.size());

  int test_count = 0;
  for (s21::List<std::string>::iterator it = lst.begin(); it != lst.end();
       ++it) {
    std::string strNumber = std::to_string(++test_count);
    ASSERT_EQ(*it, strNumber);
  }

  lst.clear();
  std_lst.clear();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(lst.size(), 0U);
}

// Pop to emplty list
TEST(ListModifiersEmpty, IntList) {
  s21::List<int> lst;
  std::list<int> std_lst;

  lst.push_back(3);
  std_lst.push_back(3);
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());

  int push_back_count = 2;
  for (s21::List<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
    ASSERT_EQ(*it, ++push_back_count);
  }

  lst.pop_back();
  std_lst.pop_back();

  lst.push_front(4);
  std_lst.push_front(4);
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());

  int push_front_count = 3;
  for (s21::List<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
    ASSERT_EQ(*it, ++push_front_count);
  }

  lst.pop_front();
  std_lst.pop_front();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_TRUE(lst.empty());

  lst.insert(lst.begin(), 1);
  std_lst.insert(std_lst.begin(), 1);
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());

  int insert_begin_count = 0;
  for (s21::List<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
    ASSERT_EQ(*it, ++insert_begin_count);
  }

  lst.clear();
  std_lst.clear();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_TRUE(lst.empty());

  lst.insert(lst.end(), 2);
  std_lst.insert(std_lst.begin(), 2);
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());

  int insert_end_count = 1;
  for (s21::List<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
    ASSERT_EQ(*it, ++insert_end_count);
  }

  lst.clear();
  std_lst.clear();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_TRUE(lst.empty());

  // проверка удаления элемента из пустого листа - спойлер не делайте так
  lst.pop_back();
  //   std_lst.pop_back();
  //   EXPECT_EQ(lst.size(), std_lst.size()); // они равны, но оригинальная
  //   функция - с утечками памяти
  EXPECT_TRUE(lst.empty());
  EXPECT_TRUE(lst.size() != 0);
}

TEST(ListModifiersEmpty, DoubleList) {
  s21::List<double> lst;
  std::list<double> std_lst;

  lst.push_back(3.0);
  std_lst.push_back(3.0);
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());

  double push_back_count = 3.0;
  for (s21::List<double>::iterator it = lst.begin(); it != lst.end(); ++it) {
    ASSERT_TRUE(*it - push_back_count < s21_EPS);
    ++push_back_count;
  }

  lst.pop_back();
  std_lst.pop_back();

  lst.push_front(4.0);
  std_lst.push_front(4.0);
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());

  double push_front_count = 4.0;
  for (s21::List<double>::iterator it = lst.begin(); it != lst.end(); ++it) {
    ASSERT_TRUE(*it - push_front_count < s21_EPS);
    ++push_front_count;
  }

  lst.pop_front();
  std_lst.pop_front();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_TRUE(lst.empty());

  lst.insert(lst.begin(), 1.0);
  std_lst.insert(std_lst.begin(), 1.0);
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());

  double insert_begin_count = 1.0;
  for (s21::List<double>::iterator it = lst.begin(); it != lst.end(); ++it) {
    ASSERT_TRUE(*it - insert_begin_count < s21_EPS);
    ++insert_begin_count;
  }

  lst.clear();
  std_lst.clear();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_TRUE(lst.empty());

  lst.insert(lst.end(), 2.0);
  std_lst.insert(std_lst.begin(), 2.0);
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());

  double insert_end_count = 2;
  for (s21::List<double>::iterator it = lst.begin(); it != lst.end(); ++it) {
    ASSERT_TRUE(*it - insert_end_count < s21_EPS);
    ++insert_end_count;
  }

  lst.clear();
  std_lst.clear();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_TRUE(lst.empty());
}

TEST(ListModifiersEmpty, StringList) {
  s21::List<std::string> lst;
  std::list<std::string> std_lst;

  lst.push_back("3");
  std_lst.push_back("3");
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.front(), "3");

  lst.pop_back();
  std_lst.pop_back();

  lst.push_front("4");
  std_lst.push_front("4");
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.front(), "4");

  lst.pop_front();
  std_lst.pop_front();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_TRUE(lst.empty());

  lst.insert(lst.begin(), "1");
  std_lst.insert(std_lst.begin(), "1");
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.front(), "1");

  lst.clear();
  std_lst.clear();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_TRUE(lst.empty());

  lst.insert(lst.end(), "2");
  std_lst.insert(std_lst.begin(), "2");
  ASSERT_EQ(lst.size(), 1U);
  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.front(), "2");

  lst.clear();
  std_lst.clear();
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_TRUE(lst.empty());
}

// swap
TEST(ListModifiers, IntSwap) {
  s21::List<int> lst{1, 2, 3, 4, 5};
  s21::List<int> lst_other{4, 3, 2, 1};

  std::list<int> std_lst{1, 2, 3, 4, 5};
  std::list<int> std_other{4, 3, 2, 1};

  lst.swap(lst_other);
  std_lst.swap(std_other);

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.size(), 4U);
  ASSERT_EQ(lst_other.size(), std_other.size());
  ASSERT_EQ(lst_other.size(), 5U);

  ASSERT_EQ(lst.front(), std_lst.front());
  ASSERT_EQ(lst.front(), 4);
  ASSERT_EQ(lst_other.front(), std_other.front());
  ASSERT_EQ(std_other.front(), 1);

  ASSERT_EQ(lst.back(), std_lst.back());
  ASSERT_EQ(lst.back(), 1);
  ASSERT_EQ(lst_other.back(), std_other.back());
  ASSERT_EQ(std_other.back(), 5);
}

TEST(ListModifiers, DoubleSwap) {
  s21::List<double> lst{1.0, 2.0, 3.0, 4.0, 5.0};
  s21::List<double> lst_other{4.0, 3.0, 2.0, 1.0};

  std::list<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};
  std::list<double> std_other{4.0, 3.0, 2.0, 1.0};

  lst.swap(lst_other);
  std_lst.swap(std_other);

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.size(), 4U);
  ASSERT_EQ(lst_other.size(), std_other.size());
  ASSERT_EQ(lst_other.size(), 5U);

  ASSERT_EQ(lst.front(), std_lst.front());
  ASSERT_EQ(lst.front(), 4.0);
  ASSERT_EQ(lst_other.front(), std_other.front());
  ASSERT_EQ(std_other.front(), 1.0);

  ASSERT_EQ(lst.back(), std_lst.back());
  ASSERT_EQ(lst.back(), 1.0);
  ASSERT_EQ(lst_other.back(), std_other.back());
  ASSERT_EQ(std_other.back(), 5.0);
}

TEST(ListModifiers, StringSwap) {
  s21::List<std::string> lst{"1", "2", "3", "4", "5"};
  s21::List<std::string> lst_other{"4", "3", "2", "1"};

  std::list<std::string> std_lst{"1", "2", "3", "4", "5"};
  std::list<std::string> std_other{"4", "3", "2", "1"};

  lst.swap(lst_other);
  std_lst.swap(std_other);

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.size(), 4U);
  ASSERT_EQ(lst_other.size(), std_other.size());
  ASSERT_EQ(std_other.size(), 5U);

  ASSERT_EQ(lst.front(), std_lst.front());
  ASSERT_EQ(lst.front(), "4");
  ASSERT_EQ(lst_other.front(), std_other.front());
  ASSERT_EQ(std_other.front(), "1");

  ASSERT_EQ(lst.back(), std_lst.back());
  ASSERT_EQ(lst.back(), "1");
  ASSERT_EQ(lst_other.back(), std_other.back());
  ASSERT_EQ(std_other.back(), "5");
}

TEST(ListModifiers, SwapSelf) {
  s21::List<int> lst{1, 2, 3, 4, 5};

  std::list<int> std_lst{1, 2, 3, 4, 5};

  lst.swap(lst);
  std_lst.swap(std_lst);

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(std_lst.size(), 5U);

  ASSERT_EQ(lst.front(), std_lst.front());
  ASSERT_EQ(std_lst.front(), 1);

  ASSERT_EQ(lst.back(), std_lst.back());
  ASSERT_EQ(std_lst.back(), 5);
}

TEST(ListModifiers, SwapEmpty) {
  s21::List<int> lst;
  s21::List<int> lst_other;

  std::list<int> std_lst;
  std::list<int> std_other;

  lst.swap(lst_other);
  std_lst.swap(std_other);

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.size(), 0U);
  ASSERT_EQ(lst_other.size(), std_other.size());
  ASSERT_EQ(lst_other.size(), 0U);
}

// merge
TEST(ListModifiers, IntMerge) {
  s21::List<int> lst{0, 2, 3, 4, 5};
  s21::List<int> lst_other{1, 6, 7, 8};

  std::list<int> std_lst{0, 2, 3, 4, 5};
  std::list<int> std_other{1, 6, 7, 8};

  lst.merge(lst_other);
  std_lst.merge(std_other);

  int count = 0;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_EQ(*it, count);
    ++count;
  }
}

TEST(ListModifiers, DoubleMerge) {
  s21::List<double> lst{0.0, 2.0, 3.0, 4.0, 5.0};
  s21::List<double> lst_other{1.0, 6.0, 7.0, 8.0};

  std::list<double> std_lst{0.0, 2.0, 3.0, 4.0, 5.0};
  std::list<double> std_other{1.0, 6.0, 7.0, 8.0};

  lst.merge(lst_other);
  std_lst.merge(std_other);

  double count = 0;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_TRUE(*it - count < s21_EPS);
    ++count;
  }
}

TEST(ListModifiers, StringMerge) {
  s21::List<std::string> lst{"0", "2", "3", "4", "5"};
  s21::List<std::string> lst_other{"1", "6", "7", "8"};

  std::list<std::string> std_lst{"0", "2", "3", "4", "5"};
  std::list<std::string> std_other{"1", "6", "7", "8"};

  lst.merge(lst_other);
  std_lst.merge(std_other);

  int count = 0;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    std::string strNumber = std::to_string(count);
    EXPECT_EQ(*it, strNumber);
    ++count;
  }
}

TEST(ListModifiers, MergeSelf) {
  s21::List<int> lst{1, 2, 3, 4, 5};

  std::list<int> std_lst{1, 2, 3, 4, 5};

  lst.merge(lst);
  std_lst.merge(std_lst);

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(std_lst.size(), 5U);

  int count = 0;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_EQ(*it, ++count);
  }
}

TEST(ListModifiers, MergeEmpty) {
  s21::List<int> lst;
  s21::List<int> lst_other;

  std::list<int> std_lst;
  std::list<int> std_other;

  lst.swap(lst_other);
  std_lst.swap(std_other);

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.size(), 0U);
  ASSERT_EQ(lst_other.size(), std_other.size());
  ASSERT_EQ(lst_other.size(), 0U);
}

// reverse
TEST(ListModifiers, IntReverse) {
  s21::List<int> lst{1, 2, 3, 4, 5};

  std::list<int> std_lst{1, 2, 3, 4, 5};

  lst.reverse();
  std_lst.reverse();

  int count = 5;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_EQ(*it, count);
    --count;
  }

  int std_count = 5;
  for (auto it = std_lst.begin(); it != std_lst.end(); ++it) {
    EXPECT_EQ(*it, std_count);
    --std_count;
  }
}

TEST(ListModifiers, DoubleReverse) {
  s21::List<double> lst{1.0, 2.0, 3.0, 4.0, 5.0};

  std::list<double> std_lst{1.0, 2.0, 3.0, 4.0, 5.0};

  lst.reverse();
  std_lst.reverse();

  double count = 5;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_TRUE(*it - count < s21_EPS);
    --count;
  }

  double std_count = 5;
  for (auto it = std_lst.begin(); it != std_lst.end(); ++it) {
    EXPECT_TRUE(*it - std_count < s21_EPS);
    --std_count;
  }
}

TEST(ListModifiers, StringReverse) {
  s21::List<std::string> lst{"1", "2", "3", "4", "5"};

  std::list<std::string> std_lst{"1", "2", "3", "4", "5"};

  lst.reverse();
  std_lst.reverse();

  int count = 5;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    std::string strNumber = std::to_string(count);
    EXPECT_EQ(*it, strNumber);
    --count;
  }

  int std_count = 5;
  for (auto it = std_lst.begin(); it != std_lst.end(); ++it) {
    std::string strNumber = std::to_string(std_count);
    EXPECT_EQ(*it, strNumber);
    --std_count;
  }
}

TEST(ListModifiers, ReverseOne) {
  s21::List<int> lst{1};

  std::list<int> std_lst{1};

  lst.reverse();
  std_lst.reverse();

  EXPECT_EQ(lst.front(), std_lst.front());
  EXPECT_EQ(std_lst.front(), 1);
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(std_lst.size(), 1U);
}

TEST(ListModifiers, ReverseEmpty) {
  s21::List<int> lst;

  std::list<int> std_lst;

  lst.reverse();
  std_lst.reverse();

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.size(), 0U);
}

// unique
TEST(ListModifiers, IntUnique) {
  s21::List<int> lst{1, 1, 1, 2, 2, 3, 4, 5};
  std::list<int> std_lst{1, 1, 1, 2, 2, 3, 4, 5};

  lst.unique();
  std_lst.unique();

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(std_lst.size(), 5U);

  int count = 0;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_EQ(*it, ++count);
  }

  int std_count = 0;
  for (auto it = std_lst.begin(); it != std_lst.end(); ++it) {
    EXPECT_EQ(*it, ++std_count);
  }
}

TEST(ListModifiers, DoubleUnique) {
  s21::List<double> lst{1.0, 1.0, 1.0, 2.0, 3.0, 4.0, 5.0};

  std::list<double> std_lst{1.0, 1.0, 1.0, 2.0, 3.0, 4.0, 5.0};

  lst.unique();
  std_lst.unique();

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.size(), 5U);

  double count = 1;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_TRUE(*it - count < s21_EPS);
    ++count;
  }

  double std_count = 1;
  for (auto it = std_lst.begin(); it != std_lst.end(); ++it) {
    EXPECT_TRUE(*it - std_count < s21_EPS);
    ++std_count;
  }
}

TEST(ListModifiers, StringUnique) {
  s21::List<std::string> lst{"1", "1", "1", "2", "3", "4", "5"};

  std::list<std::string> std_lst{"1", "1", "1", "2", "3", "4", "5"};

  lst.unique();
  std_lst.unique();

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.size(), 5U);

  int count = 1;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    std::string strNumber = std::to_string(count);
    EXPECT_EQ(*it, strNumber);
    ++count;
  }

  int std_count = 1;
  for (auto it = std_lst.begin(); it != std_lst.end(); ++it) {
    std::string strNumber = std::to_string(std_count);
    EXPECT_EQ(*it, strNumber);
    ++std_count;
  }
}

TEST(ListModifiers, UniqueOne) {
  s21::List<int> lst{1};
  std::list<int> std_lst{1};

  lst.unique();
  std_lst.unique();

  EXPECT_EQ(lst.front(), std_lst.front());
  EXPECT_EQ(std_lst.front(), 1);
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(std_lst.size(), 1U);
}

TEST(ListModifiers, UniqueEmpty) {
  s21::List<int> lst;
  std::list<int> std_lst;

  lst.unique();
  std_lst.unique();

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.size(), 0U);
}

// sort
TEST(ListModifiers, IntSort) {
  s21::List<int> lst{2, 4, 3, 1, 5};
  std::list<int> std_lst{2, 4, 3, 1, 5};

  lst.sort();
  std_lst.sort();

  int count = 0;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_EQ(*it, ++count);
  }

  int std_count = 0;
  for (auto it = std_lst.begin(); it != std_lst.end(); ++it) {
    EXPECT_EQ(*it, ++std_count);
  }
}

TEST(ListModifiers, DoubleSort) {
  s21::List<double> lst{2.0, 4.0, 3.0, 1.0, 5.0};

  std::list<double> std_lst{2.0, 4.0, 3.0, 1.0, 5.0};

  lst.sort();
  std_lst.sort();

  double count = 1;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_TRUE(*it - count < s21_EPS);
    ++count;
  }

  double std_count = 1;
  for (auto it = std_lst.begin(); it != std_lst.end(); ++it) {
    EXPECT_TRUE(*it - std_count < s21_EPS);
    ++std_count;
  }
}

TEST(ListModifiers, StringSort) {
  s21::List<std::string> lst{"2", "4", "3", "1", "5"};

  std::list<std::string> std_lst{"2", "4", "3", "1", "5"};

  lst.sort();
  std_lst.sort();

  int count = 1;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    std::string strNumber = std::to_string(count);
    EXPECT_EQ(*it, strNumber);
    ++count;
  }

  int std_count = 1;
  for (auto it = std_lst.begin(); it != std_lst.end(); ++it) {
    std::string strNumber = std::to_string(std_count);
    EXPECT_EQ(*it, strNumber);
    ++std_count;
  }
}

TEST(ListModifiers, SortOne) {
  s21::List<int> lst{1};
  std::list<int> std_lst{1};

  lst.sort();
  std_lst.sort();

  EXPECT_EQ(lst.front(), std_lst.front());
  EXPECT_EQ(std_lst.front(), 1);
  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(std_lst.size(), 1U);
}

TEST(ListModifiers, SortEmpty) {
  s21::List<int> lst;
  std::list<int> std_lst;

  lst.sort();
  std_lst.sort();

  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(std_lst.size(), 0U);
}

// splice
TEST(ListModifiers, IntSplice) {
  s21::List<int> lst{5, 6, 7, 8, 9};
  s21::List<int> lst_other{1, 2, 3, 4};

  std::list<int> std_lst{5, 6, 7, 8, 9};
  std::list<int> std_other{1, 2, 3, 4};

  lst.splice(lst.begin(), lst_other);
  std_lst.splice(std_lst.begin(), std_other);

  int count = 0;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_EQ(*it, ++count);
  }

  s21::List<int> lst_end{10, 11, 12};
  std::list<int> std_end{10, 11, 12};
  lst.splice(lst.end(), lst_end);
  std_lst.splice(std_lst.end(), std_end);

  int count_end = 0;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_EQ(*it, ++count_end);
  }

  EXPECT_EQ(lst.size(), std_lst.size());
  EXPECT_EQ(count_end, 12);
  EXPECT_EQ(lst.size(), 12U);
}

TEST(ListModifiers, DoubleSplice) {
  s21::List<double> lst{5.0, 6.0, 7.0, 8.0, 9.0};
  s21::List<double> lst_other{1.0, 2.0, 3.0, 4.0};

  std::list<double> std_lst{5.0, 6.0, 7.0, 8.0, 9.0};
  std::list<double> std_other{1.0, 2.0, 3.0, 4.0};

  lst.splice(lst.begin(), lst_other);
  std_lst.splice(std_lst.begin(), std_other);

  double count = 1;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    EXPECT_TRUE(*it - count < s21_EPS);
    ++count;
  }
}

TEST(ListModifiers, StringSplice) {
  s21::List<std::string> lst{"5", "6", "7", "8", "9"};
  s21::List<std::string> lst_other{"1", "2", "3", "4"};

  std::list<std::string> std_lst{"5", "6", "7", "8", "9"};
  std::list<std::string> std_other{"1", "2", "3", "4"};

  lst.splice(lst.begin(), lst_other);
  std_lst.splice(std_lst.begin(), std_other);

  int count = 1;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    std::string strNumber = std::to_string(count);
    EXPECT_EQ(*it, strNumber);
    ++count;
  }
}

TEST(ListModifiers, SpliceEmpty) {
  s21::List<int> lst;
  s21::List<int> lst_other;

  std::list<int> std_lst;
  std::list<int> std_other;

  lst.splice(lst.begin(), lst_other);
  std_lst.splice(std_lst.begin(), std_other);

  ASSERT_EQ(lst.size(), std_lst.size());
  ASSERT_EQ(lst.size(), 0U);
  ASSERT_EQ(lst_other.size(), std_other.size());
  ASSERT_EQ(lst_other.size(), 0U);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}