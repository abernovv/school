#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Flags flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int flag_index_file_pattern[1000] = {};
  int flag_index_e_pattern[1000] = {};
  char *pattern = NULL;
  int file_start_index;

  if (parseFlags(argc, argv, &flags, &pattern, &file_start_index,
                 flag_index_file_pattern, flag_index_e_pattern)) {
    int multiple_files = argc - file_start_index -
                         arr_len(flag_index_file_pattern) -
                         arr_len(flag_index_e_pattern) - 1;
    if (arr_len(flag_index_file_pattern) + arr_len(flag_index_e_pattern) == 0)
      multiple_files -= 1;

    multiple_files = multiple_files > 1 ? 1 : 0;

    // -f flag
    if (flags.f) {
      char *token = strtok(pattern, "\n");
      while (token != NULL) {
        for (int i = 1; i < argc; i++) {
          if (argv[i][0] != '-' && !count_index(flag_index_file_pattern, i) &&
              !count_index(flag_index_e_pattern, i))
            grepFile(argv[i], token, flags, multiple_files);
        }
        token = strtok(NULL, "\n");
      }
    } else {
      for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-' && !count_index(flag_index_file_pattern, i) &&
            !count_index(flag_index_e_pattern, i)) {
          if (pattern == NULL) {
            pattern = argv[i];
          } else {
            grepFile(argv[i], pattern, flags, multiple_files);
          }
        }
      }
    }
    if (flags.f && pattern != NULL) {
      free(pattern);
    }
  }

  return 0;
}

int parseFlags(int argc, char *argv[], Flags *flags, char **pattern,
               int *file_start_index, int *flag_index_file_pattern,
               int *flag_index_e_pattern) {
  int ret = 1;
  *file_start_index = 0;
  *pattern = NULL;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      for (int j = 1; j < (int)strlen(argv[i]); j++) {
        if (argv[i][j] == 'e') {
          flags->e = 1;
          flag_e(argc, i, &ret, flag_index_e_pattern);
          *pattern =
              argv[flag_index_e_pattern[arr_len(flag_index_e_pattern) - 1]];
        } else if (argv[i][j] == 'i') {
          flags->i = 1;
        } else if (argv[i][j] == 'v') {
          flags->v = 1;
        } else if (argv[i][j] == 'c') {
          flags->c = 1;
        } else if (argv[i][j] == 'l') {
          flags->l = 1;
        } else if (argv[i][j] == 'n') {
          flags->n = 1;
        } else if (argv[i][j] == 'h') {
          flags->h = 1;
        } else if (argv[i][j] == 's') {
          flags->s = 1;
        } else if (argv[i][j] == 'f') {
          if (flags->f && *pattern != NULL) {
            free(*pattern);
          }
          flags->f = 1;
          flag_f(argc, argv, i, pattern, &ret, flag_index_file_pattern);
        } else if (argv[i][j] == 'o') {
          flags->o = 1;
        } else {
          printf("s21_grep: illegal option -- %s\n", argv[i]);
          printUsage();
          ret = 0;
        }
      }
      *file_start_index += 1;
    }
  }

  if (argc - *file_start_index < 3 && ret) {
    printUsage();
    ret = 0;
  }

  return ret;
}

void flag_e(int argc, int i, int *ret, int *flag_index_e_pattern) {
  if (i + 1 < argc) {
    flag_index_e_pattern[arr_len(flag_index_e_pattern)] = i + 1;
  } else {
    printf("s21_grep: option requires an argument -- e\n");
    printUsage();
    *ret = 0;
  }
}

void flag_f(int argc, char **argv, int i, char **pattern, int *ret,
            int *flag_index_file_pattern) {
  if (i + 1 < argc) {
    FILE *pattern_file = fopen(argv[++i], "r");
    if (pattern_file == NULL) {
      printf("s21_grep: %s: No such file or directory\n", argv[i]);
      *ret = 0;
    } else {
      fseek(pattern_file, 0, SEEK_END);
      long fsize = ftell(pattern_file);
      fseek(pattern_file, 0, SEEK_SET);

      *pattern = malloc(fsize + 1);
      fread(*pattern, 1, fsize, pattern_file);
      fclose(pattern_file);
      flag_index_file_pattern[arr_len(flag_index_file_pattern)] = i;

      (*pattern)[fsize] = '\0';
    }
  } else {
    printf("s21_grep: option requires an argument -- f\n");
    printUsage();
    *ret = 0;
  }
}

void grepFile(char *filename, char *pattern, Flags flags, int multiple_files) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    if (!flags.s) {
      printf("s21_grep: %s: No such file or directory\n", filename);
    }
  } else {
    char line[1024];
    char copy_line[1024];
    int line_number = 0;
    int match_count = 0;

    if (flags.i) {
      toLowerStr(pattern);
    }

    while (fgets(line, sizeof(line), file)) {
      line_number++;

      strcpy(copy_line, line);
      if (flags.i) {
        toLowerStr(copy_line);
      }

      if (strstr(copy_line, pattern) != NULL && !flags.v) {
        match_count++;
        if (!(flags.c || flags.l)) {
          if (multiple_files && !flags.h) {
            printf("%s:", filename);
          }
          if (flags.n) {
            printf("%d:", line_number);
          }
          printf("%s", line);
        }
      } else if (strstr(copy_line, pattern) == NULL && flags.v) {
        match_count++;
        if (!(flags.c || flags.l)) {
          if (multiple_files && !flags.h) {
            printf("%s:", filename);
          }
          if (flags.n) {
            printf("%d:", line_number);
          }
          printf("%s", line);
        }
      }
    }

    // Оригинальный grep при одновременных флалах -c и -l выводит единицу, для
    // это нужно условие ниже
    if (flags.c && flags.l && match_count > 0) {
      printf("1\n%s\n", filename);
    } else {
      if (flags.c) {
        printf("%d\n", match_count);
      }

      if (flags.l && match_count > 0) {
        printf("%s\n", filename);
      }
    }

    fclose(file);
  }

  return;
}

int arr_len(int *arr) {
  int index = 0;
  for (; arr[index] != 0;) {
    index++;
  }
  return index;
}

int count_index(int *arr, int index) {
  int flag = 0;
  int len = arr_len(arr);
  for (int i = 0; i < len; i++) {
    if (arr[i] == index) flag = 1;
  }
  return flag;
}

void toLowerStr(char *str) {
  if (str == NULL) {
    return;
  }

  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}

void printUsage() {
  printf(
      "usage: ./s21_grep [-e pattern] [-i] [-v] [-c] [-l] [-n] [-h] [-s] [-f "
      "file] [pattern] [file ...]\n"
      "Options:\n"
      "  -e pattern  Use pattern as the pattern. Can be used multiple times.\n"
      "  -i          Ignore case distinctions.\n"
      "  -v          Invert the sense of matching, to select non-matching "
      "lines.\n"
      "  -c          Print only a count of matching lines per FILE.\n"
      "  -l          Print only names of FILEs with selected lines.\n"
      "  -n          Prefix each line of output with the 1-based line number "
      "within its input file.\n"
      "  -h          Suppress the prefixing of file names on output.\n"
      "  -s          Suppress error messages about nonexistent or unreadable "
      "files.\n"
      "  -f file     Obtain patterns from FILE, one per line.\n");
}