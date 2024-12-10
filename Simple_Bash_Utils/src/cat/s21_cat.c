
#include "s21_cat.h"

int main(int argc, char **argv) {
  struct flags flag = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 1; i < argc; i++) {
    init_flags(&flag, argv[i]);
  }
  int cnt = 1;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') open_file(argv[i], &flag, &cnt);
  }
  return 0;
}

void init_flags(struct flags *flag, char *argv) {
  if (argv[0] == '-' && argv[1] != '-') {
    for (int i = 0; i < (int)strlen(argv); i++) {
      if (argv[i] == 'b')
        flag->b = 1;
      else if (argv[i] == 'E')
        flag->E = 1;
      else if (argv[i] == 'e')
        flag->e = 1;
      else if (argv[i] == 'n')
        flag->n = 1;
      else if (argv[i] == 's')
        flag->s = 1;
      else if (argv[i] == 'T')
        flag->T = 1;
      else if (argv[i] == 't')
        flag->t = 1;
    }
  }
  if (flag->t == 1 || flag->e == 1) flag->v = 1;
}

void open_file(char *argv, struct flags *flag, int *cnt) {
  FILE *fp = fopen(argv, "r");

  if (fp != NULL) {
    s21_cat(flag, fp, cnt);
    fclose(fp);
  } else {
    printf("\ncat: %s: No such file of directory", argv);
  }
}

void s21_cat(struct flags *flag, FILE *fp, int *cnt) {
  int cnt_start = *cnt;
  char sym = ' ', pred_sym = ' ';
  while (1) {
    char pred_pred_sym = pred_sym;
    pred_sym = sym;
    if ((sym = getc(fp)) == EOF) {
      break;
    }
    if (flag->s != 1 || pred_sym != '\n' || sym != '\n' ||
        pred_pred_sym != '\n') {
      if ((pred_sym == '\n') ||
          (*cnt == cnt_start && (flag->n == 1 || flag->b == 1))) {
        if ((flag->n == 1 && flag->b == 0) || (flag->b == 1 && sym != '\n')) {
          printf("%6d\t", *cnt);
          *cnt += 1;
        }
      }
      if (sym == '\n') {
        if (flag->e == 1) {
          printf("$");
        }
      }
      if (sym == '\t' && flag->t == 1) {
        printf("^I");
      } else if (sym < 32 && flag->v == 1 && sym != 9 && sym != 10) {
        printf("^%c", sym + 64);
      } else {
        printf("%c", sym);
      }
    }
  }
}