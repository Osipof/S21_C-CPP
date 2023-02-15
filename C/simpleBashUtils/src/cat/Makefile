CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OBJECTS = s21_cat.o
SOURCES = s21_cat.c
.PHONY: all s21_cat
all: s21_cat
s21_cat:
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(CFLAGS) $(OBJECTS) -o s21_cat
clean:
	rm -rf *.o
	rm -rf s21_cat
rebuild:
	$(MAKE) clean
	$(MAKE) all