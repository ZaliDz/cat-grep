FLAGS = -Wall -Werror -Wextra -g

all: s21_grep 

s21_grep: clean check
	gcc $(FLAGS) s21_grep.c -o s21_grep

check: 
	clang-format -style=Google -n *.c *.h
	clang-format -style=Google -i *.c *.h

clean:
	rm -rf s21_grep