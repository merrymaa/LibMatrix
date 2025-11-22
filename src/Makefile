CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++20
LIBS = -lgtest -lgtest_main -lpthread
COVERAGE_FLAGS = --coverage

TARGET_LIB = s21_matrix_oop.a
TEST_NAME = matrix_test

SRC = $(wildcard *.cpp)
SRC_TEST = $(wildcard $(PATH_TEST)*.cpp)

OBJ = $(patsubst %.cpp, $(PATH_OBJ)%.o, $(SRC))
OBJ_COV = $(patsubst %.cpp, $(PATH_OBJ_COV)%_gcov.o, $(SRC))
OBJ_TEST = $(patsubst $(PATH_TEST)%.cpp, $(PATH_OBJ_TEST)%.o, $(SRC_TEST))

PATH_OBJ = ./obj/lib/
PATH_OBJ_COV = ./obj/cov/
PATH_OBJ_TEST = ./obj/test/
PATH_TEST = ./tests/

all : s21_matrix_oop.a gcov_report

s21_matrix_oop.a : $(OBJ)
	@printf "\033[0;32mbuilding static library...\033[0m\n" >&2
	@ar rcs $(TARGET_LIB) $(OBJ)

s21_matrix_oop_cov.a : $(OBJ_COV)
	@ar rcs s21_matrix_oop_cov.a $(OBJ_COV)

test : s21_matrix_oop_cov.a $(OBJ_TEST)
	@printf "\033[0;32mrunning tests...\033[0m\n" >&2
	@$(CC) $(CFLAGS) $(OBJ_TEST) -o $(TEST_NAME) $(COVERAGE_FLAGS) -L. -l:s21_matrix_oop_cov.a $(LIBS)
	@./$(TEST_NAME) --gtest_color=yes --gtest_brief

# подробный вывод тестов
test_full :
	./$(TEST_NAME) --gtest_color=yes 

gcov_report : test
	@lcov -t "matrix_test" -o test.info -c -d .
	@-mkdir report
	@genhtml -o report test.info
	@open report/index.html

rebuild : clean all

# main : main.o $(OBJ)
# 	$(CC) $(CFLAGS) ./main/main.o  $(OBJ) -o ./main/main
# 	./main/main

#main.o : ./main/main.cpp
#	g++ $(CFLAGS) -std=c++20 -c ./main/main.cpp -o ./main/main.o

$(PATH_OBJ)%.o : %.cpp
	@-mkdir -p ./obj/
	@-mkdir -p ./obj/lib/
	@$(CC) $(CFLAGS) -c $< -o $@

$(PATH_OBJ_COV)%_gcov.o : %.cpp
	@-mkdir -p ./obj/
	@-mkdir -p ./obj/cov
	@$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

$(PATH_OBJ_TEST)%.o : $(PATH_TEST)%.cpp
	@-mkdir -p ./obj/
	@-mkdir -p ./obj/test
	@$(CC) $(CFLAGS) -c $< -o $@

# изменение стиля
format :
	clang-format -i *.h *.cpp ./tests/*.cpp

# прверка на соответствие стилю
style :
	clang-format -n *.h *.cpp ./tests/*.cpp

valgrind :
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_NAME)

clean :
	@-rm -rf ./main/*.o
	@-rm -rf ./obj
	@-rm -rf ./report
	@-rm -rf $(TEST_NAME) test.info s21_matrix_oop_cov.a $(TARGET_LIB)
	@-rm -rf ./main/main
	@echo "\033[0;32mcleaning...\033[0m"
	@echo "done"





