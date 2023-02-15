CC:= gcc -Wall -Werror -Wextra -std=c11
DLIB = -lcheck

ifeq ($(uname -s), Linux)
	DLIB += -lsubunit -lm -lpthread -pthread -lrt
endif

all: clean s21_math.a test gcov_report

clean: 
	rm -rf *.a *.out *.o report *.gc* *.info test gcov*

test:
	$(CC) test.c s21_*.c $(DLIB) -o test
	./test
	
s21_math.a:
	$(CC) -c s21_*.c
	ar rcs s21_math.a s21_*.o

gcov_report: s21_math.a
	$(CC) --coverage test.c s21_math.a $(DLIB) -o gcov_test
	chmod +x gcov_test
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

linter:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c *.h 
	rm -rf .clang-format

