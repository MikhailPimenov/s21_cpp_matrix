CC = g++
# -ltest - Link with the Google Test libaray
TEST_LIB = -lgtest
TEST_DIR = tests/
FLAGS = -Wall -Werror -Wextra -Wpedantic -std=c++17 -fsanitize=address -fsanitize=undefined

VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER = valgrind_report

.PHONY: test

tests_main: 
	$(CC) $(FLAGS) $(TEST_DIR)tests_main.cc s21_cpp_matrix.cc -o tests_main.out $(TEST_LIB)

test_constructor:
	$(CC) $(FLAGS) -o test_constructor.out s21_cpp_matrix.cc

test: tests_main
	-./tests_main.out

clean:
	rm -f *.a *.out $(TEST_DIR)*.o $(TEST_DIR).out

valgrind: test
	mkdir -p $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/
	-valgrind --leak-check=full --show-reachable=no --track-origins=yes --log-file=$(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/valgrind_report.txt -s ./tests_main.out > $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/test_report.txt
	cat $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/test_report.txt
	cat $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/valgrind_report.txt

valgrind_full: test
	mkdir -p $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)
	-valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/valgrind_full_report.txt -s ./tests/tests_main.exe > $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/test_report.txt
	cat $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/test_report.txt
	cat $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/valgrind_full_report.txt
