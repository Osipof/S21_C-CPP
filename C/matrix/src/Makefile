CC= gcc -std=c11
CFLAGS= -Wall -Wextra -Werror
TEST= *.c
TEST_FLAGS = -lcheck

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
    TEST_FLAGS = -lcheck
else
	TEST_FLAGS = -lcheck -lpthread -pthread -lrt -lm -lsubunit
endif

all: s21_matrix.a

test: clean
		$(CC) $(CFLAGS)  $(TEST) -o test $(TEST_FLAGS)

gcov_report: clean
		$(CC) --coverage $(CFLAGS) $(TEST) -o test $(TEST_FLAGS)
		./test
		lcov -t "test" -o test.info -c -d .
		genhtml -o report test.info
		open report/index.html

clean:
	rm -rf test
	rm -rf *.a *.out *.o report *.gc* s21_matrix.a *.info

run:
	./test

s21_matrix.a: clean
		$(CC) $(CFLAGS) s21_matrix.c -c
		ar rcs s21_matrix.a *.o

rebuild:
	make clean
	make all

leak:
	CK_FORK=no leaks --atExit -- ./test

linter:
	cp ../materials/linters/.clang-format ..
	clang-format -i *.c *.h
	clang-format -n *.c *.h
	rm -rf ../.clang-format

