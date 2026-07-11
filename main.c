#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 4096

typedef struct {
  int number_lines;
  int number_nonblank;
  int squeeze_blank;
} Flags;

Flags parse_flags(int argc, char *argv[], int *file_start) {
  Flags flags = {0, 0, 0};
  int i;

  for (i = 1; i < argc; i++) {
    if (argv[i][0] != '-') break;

    if (strcmp(argv[i], "--number") == 0) {
      flags.number_lines = 1;
    } else if (strcmp(argv[i], "--number-nonblank") == 0) {
      flags.number_nonblank = 1;
    } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
      flags.squeeze_blank = 1;
    } else if (strcmp(argv[i], "--") == 0) {
      i++;
      break;
    } else {
      char *p = &argv[i][1];
      while (*p) {
        switch (*p) {
          case 'n': flags.number_lines = 1; break;
          case 'b': flags.number_nonblank = 1; break;
          case 's': flags.squeeze_blank = 1; break;
          default:
            fprintf(stderr, "mewc: invalid option -- '%c'\n", *p);
            exit(1);
        }
        p++;
      }
    }
  }

  *file_start = i;
  return flags;
}

void display_file(FILE *fp, Flags *flags, int *line_num) {
  char line[MAX_LINE];
  int prev_blank = 0;

  while (fgets(line, sizeof(line), fp)) {
    int is_blank = (line[0] == '\n' || line[0] == '\0');

    if (flags->squeeze_blank) {
      if (is_blank) {
        if (prev_blank) continue;
        prev_blank = 1;
      } else {
        prev_blank = 0;
      }
    }

    if (flags->number_nonblank) {
      if (!is_blank) {
        printf("%6d\t", (*line_num)++);
      }
    } else if (flags->number_lines) {
      printf("%6d\t", (*line_num)++);
    }

    fputs(line, stdout);
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    FILE *fp = stdin;
    Flags flags = {0, 0, 0};
    int line_num = 1;
    display_file(fp, &flags, &line_num);
    return 0;
  }

  int file_start;
  Flags flags = parse_flags(argc, argv, &file_start);
  int line_num = 1;
  int had_files = 0;
  int exit_code = 0;

  for (int i = file_start; i < argc; i++) {
    had_files = 1;

    if (strcmp(argv[i], "-") == 0) {
      display_file(stdin, &flags, &line_num);
      continue;
    }

    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      fprintf(stderr, "mewc: %s: No such file or directory\n", argv[i]);
      exit_code = 1;
      continue;
    }

    display_file(fp, &flags, &line_num);
    fclose(fp);
  }

  if (!had_files) {
    display_file(stdin, &flags, &line_num);
  }

  return exit_code;
}
