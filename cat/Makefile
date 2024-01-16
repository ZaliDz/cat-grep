FLAGS = -Wall -Werror -Wextra -g

all: s21_cat

s21_cat: clean check
	gcc $(FLAGS) s21_cat.c -o s21_cat

check: 
	clang-format -style=Google -n *.c
	clang-format -style=Google -i *.c

clean:
	rm -rf s21_cat 