CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OBJECTS = s21_grep.o
SOURCES = s21_grep.c
.PHONY: all s21_grep
all: s21_grep
s21_grep:
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(CFLAGS) $(OBJECTS) -o s21_grep
clean:
	rm -rf *.o
	rm -rf s21_grep
rebuild:
	$(MAKE) clean
	$(MAKE) all