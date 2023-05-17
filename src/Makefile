CC = g++
# -ltest - Link with the Google Test libaray
TEST_LIB = -lgtest
TEST_DIR = tests/
FLAGS = -Wall -Werror -Wextra -Wpedantic -std=c++17 -fsanitize=address -fsanitize=undefined

.PHONY: test

tests_main: 
	$(CC) $(FLAGS) $(TEST_DIR)tests_main.cc s21_cpp_matrix.cc -o tests_main.out $(TEST_LIB)

test_constructor:
	$(CC) $(FLAGS) -o test_constructor.out s21_cpp_matrix.cc

test: tests_main
	./tests_main.out

clean:
	rm -f *.a *.out $(TEST_DIR)*.o $(TEST_DIR).out
