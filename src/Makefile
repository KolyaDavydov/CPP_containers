GCC = g++ -Wall -Wextra -Werror
LIBS = -lgtest
LINUX = -lsubunit -lrt -lpthread -lm
VALGRIND_FLAGS = --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
OS = $(shell uname -s)

TEST_SRC = *.cc
OBJ = $(SRC:.cc=.o)

ifeq ($(OS), Linux)
	LIBS += -lgmock -pthread
endif

all: clean valgrind

test: clean
	$(GCC) $(TEST_SRC) -o test $(LIBS)
	./test --gtest_repeat=10 --gtest_break_on_failure

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
	clang-format -style=Google -i *.cc *.h
	clang-format -style=Google -n *.cc *.h
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
