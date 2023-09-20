GCC = gcc -Wall -Werror -Wextra -std=c11
TST_LIBS = -lcheck
OS := $(shell uname -s)


ifeq ($(OS),Linux)
		CC+=-D LINUX_OS
		TST_LIBS+= -lrt -lm -lpthread
else
	ifeq ($(OS),Darwin)
		CC+=-D MAC_OS
		TST_LIBS+=-lm -lpthread
	endif
endif


all: clean s21_decimal.a test gcov_report

clean:
	rm -rf *.a && rm -rf *.o *.exe
	rm -rf *.info && rm -rf *.gcda && rm -rf *.gcno &&  rm -rf *.gcov *.html *.css *.cfg
	rm -rf report/ && rm -rf *.out
	rm -rf .clang-format

s21_decimal.a: clean
	$(GCC) -c s21_decimal.c -o ./s21_decimal.o
	ar rcs s21_decimal.a s21_decimal.o
	ranlib s21_decimal.a


test: s21_decimal.a
	$(GCC) tests.c -L. s21_decimal.a $(TST_LIBS) -o ./tests.exe
	$(GCC) --coverage tests.c s21_decimal.c s21_decimal.a -L. s21_decimal.a $(TST_LIBS) -o ./tests.exe
	./tests.exe

gcov_report: s21_decimal.a test
	./tests.exe
	gcov -a -f s21_decimal.gcda
	gcovr --html-details -o report.html

check:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c
	clang-format -n *.h
	cppcheck *.c
	cppcheck *.h
