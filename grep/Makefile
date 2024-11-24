CC=gcc

CFLAGS=-std=c11 -Wall -Wextra  -Werror -D_GNU_SOURCE

ALL: clean s21_grep

s21_grep:
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

test:
	bash test_func_grep.sh

clean:
	rm -rf s21_grep s21_grep.dSYM *.o 