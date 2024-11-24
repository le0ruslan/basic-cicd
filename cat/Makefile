CC=gcc

CFLAGS=-std=c11 -Wall -Wextra -Werror
ALL: clean s21_cat

s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

test:
	bash test_func_cat.sh


clean:
	rm -rf s21_cat s21_cat.dSYM *.o