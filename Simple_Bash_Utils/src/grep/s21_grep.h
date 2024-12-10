
#ifndef S21GREP
#define S21GREP

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  // More flags
  int h;
  int s;
  int f;
  int o;
} Flags;

int parseFlags(int argc, char *argv[], Flags *flags, char **pattern,
               int *file_start_index, int *flag_index_file_pattern,
               int *flag_index_e_pattern);
void grepFile(char *filename, char *pattern, Flags flags, int multiple_files);
void printUsage();
void toLowerStr(char *str);
void flag_e(int argc, int i, int *ret, int *flag_index_e_pattern);

void flag_f(int argc, char **argv, int i, char **pattern, int *ret,
            int *flag_index_file_pattern);
int arr_len(int *arr);
int count_index(int *arr, int index);

#endif  // S21GREP

/*

1	-e	Шаблон.
2	-i	Игнорирует различия регистра.
3	-v	Инвертирует смысл поиска соответствий.
4	-c	Выводит только количество совпадающих строк.
5	-l	Выводит только совпадающие файлы.
6	-n	Предваряет каждую строку вывода номером строки из файла ввода.

*/