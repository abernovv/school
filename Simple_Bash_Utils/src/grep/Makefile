CFLAGS = -Wall -Wextra -Werror -std=c11


s21_grep :
	gcc $(CFLAGS) s21_grep.c -o s21_grep

format :
	cp ../../materials/linters/.clang-format .
	clang-format -n *.c *.h
	clang-format -i *.c *.h

check: format
	cppcheck  *.c *.h --check-level=exhaustive

clean :
	rm -f s21_grep *.o .clang-format
 	