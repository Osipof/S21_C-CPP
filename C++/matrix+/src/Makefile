.PHONY: all clean test $(SOURCENAME).a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
TFLAGS = -lgtest -pthread
SOURCENAME = s21_matrix_oop

ifeq ($(shell uname -s),Linux)
	CC = g++
endif


all: $(SOURCENAME).a test

$(SOURCENAME).a: $(SOURCENAME).h
	@$(CC) $(CFLAGS) -c $(SOURCENAME).cc
	@ar rc $(SOURCENAME).a $(SOURCENAME).o
	@ranlib $(SOURCENAME).a
	@rm $(SOURCENAME).o


test: $(SOURCENAME).cc test.cc $(SOURCENAME).h
	@$(CC) $(CFLAGS) $(SOURCENAME).cc test.cc -o test $(TFLAGS)
	@./test


clean:
	@-rm -rf *.o *.a test

style:
	@clang-format -style=google -n s21_matrix_oop.cc s21_matrix_oop.h test.cc
	@clang-format -style=google -i s21_matrix_oop.cc s21_matrix_oop.h test.cc