GCC = g++ -std=c++17 -Wall -Wextra -Werror
LIBS = -lgtest
LINUX = -lsubunit -lrt -lpthread -lm
DEBUG = -fsanitize=address
VALGRIND_FLAGS = --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
OS = $(shell uname -s)

TEST_SRC = all_tests/*.cc
OBJ = $(SRC:.cc=.o)

ifeq ($(OS), Linux)
	LIBS += -lgmock -pthread
endif

all: clean valgrind

# ВРЕМЕННАЯ ЦЕЛЬ ДЛЯ ТЕСТИРОВАНИЯ s21_set.h
st: clean
	$(GCC) s21_test_set.cc -o test $(LIBS)
	./test
# ВРЕМЕННАЯ ЦЕЛЬ ДЛЯ ПРОВЕРКИ КОМПИЛЯЦИИ tree.h
main: clean
	$(GCC) main.cpp -o main
	./main
# ВРЕМЕННАЯ ЦЕЛЬ ДЛЯ ТЕСТИРОВАНИЯ tree.h
mt: clean
	$(GCC) tree_test.cc -o test $(LIBS)
	./test
# ВРЕМЕННАЯ ЦЕЛЬ ДЛЯ УТЕЧЕК tree.h
vt: clean mt
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --log-file=RESULT_VALGRIND.txt ./test

test: clean
	$(GCC) $(DEBUG) $(TEST_SRC) -o test $(LIBS)
	./test --gtest_repeat=10 --gtest_break_on_failure

# ТОЛько для линукс
valgrind: clean
	$(GCC) $(TEST_SRC) -o test $(LIBS) $(LINUX)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./test

gcov_report: clean
	$(GCC) --coverage $(TEST_SRC) -o test $(LIBS)
	chmod +x test
	./test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info

	open ./report/index.html

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i all_tests/*.cc
	clang-format -style=Google -i *.h
	clang-format -style=Google -n all_tests/*.cc
	clang-format -style=Google -n *.h
	rm .clang-format

clean:
	rm -rf a.out*
	rm -rf gtest.*o
	rm -rf report
	rm -rf test*
	rm -rf *.gcda
	rm -rf *.dSYM
	rm -rf *.gcno
	rm -rf RESULT_VALGRIND.txt
	rm -rf main

