CC = g++ -std=c++17 -Wall -Werror -Wextra -Wpedantic
TEST_FLAGS =-lgtest

all: clean test

test: clean
	$(CC) test.cc $(TEST_FLAGS) -o test
	./test

clang:
	clang-format -style=Google -n *.cc  *.h

leaks_test: clean test
ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --log-file=RESULT_VALGRIND.txt ./test
endif

clean:
	@rm -rf *.o *.a report.info *.gcda *.gcno report RESULT_VALGRIND.txt test
