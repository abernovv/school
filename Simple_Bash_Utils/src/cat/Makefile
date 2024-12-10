CFLAGS = -Wall -Wextra -Werror -std=c11

s21_cat: 
	gcc $(CFLAGS) s21_cat.c -o s21_cat

format:
	cp ../../materials/linters/.clang-format .
	clang-format -n *.c *.h
	clang-format -i *.c *.h

check: format
	cppcheck *.c *.h --check-level=exhaustive

clean: 
	rm -f s21_cat *.o.clang-format
