CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11

all: s21_string.a 

clean:
	rm -rf *.a *.o
	rm -rf s21_test
	rm -rf logs

s21_string.a:
	$(CC) $(FLAGS) -c s21_string.c s21_sprintf.c s21_sscanf.c
	ar rcs s21_string.a *.o
	ranlib s21_string.a
	rm *.o

test: s21_string.a
	$(CC) $(FLAGS) test_unit.c -L. s21_string.a -lcheck -lm -lpthread -lsubunit -o s21_test
	./s21_test

gcov_report: s21_string.a
	mkdir logs
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage test_unit.c s21_string.c s21_sprintf.c  s21_sscanf.c -o logs/gcov -lcheck -lm -lsubunit
	./logs/gcov
	gcovr --html-details -o logs/index.html --exclude test_unit.c
	rm logs/*.gcda logs/*.gcno logs/gcov

rebuild: clean s21_string.a 

check_style:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h 