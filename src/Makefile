CC = g++
# -ltest - Link with the Google Test libaray
TEST_LIB = -lgtest
TEST_DIR = tests/
FLAGS = -Wall -Werror -Wextra -Wpedantic -std=c++17 -fsanitize=address -fsanitize=undefined
SOURCES = s21_matrix_oop.cc s21_helpers.cc s21_exception_handling.cc

VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER = valgrind_report

.PHONY: all test gcov_report clean valgrind

all: clean s21_matrix_oop.a 

s21_matrix_oop.a:
	$(CC) $(FLAGS) -c $(SOURCES)
	ar rvs s21_matrix_oop.a *.o

test: 
	$(CC) $(FLAGS) $(TEST_DIR)tests_main.cc $(SOURCES) -o tests.out $(TEST_LIB)
	./tests.out

gcov_report: test
	$(CC) --coverage $(FLAGS) $(TEST_DIR)tests_main.cc $(SOURCES) -o tests_coverage.out $(TEST_LIB)
	./tests_coverage.out
	lcov --directory . --capture --output-file coverage.info
	lcov --remove coverage.info '/usr/*' '*/gtest/*' '*/tests/*' --output-file coverage.info.cleaned
	genhtml coverage.info.cleaned --output-directory coverage_report
	open coverage_report/index.html

clean:
	rm -f *.a *.out *.o $(TEST_DIR)*.o $(TEST_DIR).out *.gcno *.gcda *.info *.info.cleaned
	rm -rf $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER) coverage_report

check_style:
	-clang-format --style=Google -n *.cc
	-clang-format --style=Google -n *.h
	-clang-format --style=Google -n tests/*.cc
	-clang-format --style=Google -n tests/*.h

style_google:
	-clang-format --style=Google -i *.cc
	-clang-format --style=Google -i *.h
	-clang-format --style=Google -i tests/*.cc
	-clang-format --style=Google -i tests/*.h

valgrind: test
	mkdir -p $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)
	-valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/valgrind_full_report.txt -s ./tests/tests_main.exe > $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/test_report.txt
	cat $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/test_report.txt
	cat $(VALGRIND_REPORT_DIRECTORY_FOR_DOCKER_CONTAINER)/valgrind_full_report.txt
