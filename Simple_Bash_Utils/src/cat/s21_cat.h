#ifndef S21CAT
#define S21CAT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flags {
  int b;
  int e;
  int E;
  int n;
  int s;
  int v;
  int t;
  int T;
};

void open_file(char *argv, struct flags *flag, int *cnt);
void init_flags(struct flags *flag, char *argv);
void s21_cat(struct flags *flag, FILE *fp, int *cnt);

#endif  // S21CAT
