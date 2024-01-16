#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct flags {
  int flag_e;
  int flag_v;
  int flag_t;
  int flag_b;
  int flag_n;
  int flag_s;
} op;
op flags = {0};
void working(FILE *file, op flags);
int parser(int argc, char *argv[], op *flags);

int main(int argc, char *argv[]) {
  int check_parser = 0;
  check_parser = parser(argc, argv, &flags);
  if (check_parser == 0) {
    FILE *file;
    for (int i = optind; i < argc; ++i) {
      if ((file = fopen(argv[i], "r")) == NULL) {
        fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
        return 1;
      }
      working(file, flags);

      fclose(file);
    }
  }
  return 0;
}

int parser(int argc, char *argv[], op *flags) {
  const char *short_options = "+benstvET";
  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'}};
  int rez = 0;
  int option_index = 0;
  while ((rez = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    if (rez == 'b') {
      flags->flag_b = 1;
    } else if (rez == 'e') {
      flags->flag_e = 1;
      flags->flag_v = 1;
    } else if (rez == 'v') {
      flags->flag_v = 1;
    } else if (rez == 'n') {
      flags->flag_n = 1;
    } else if (rez == 's') {
      flags->flag_s = 1;
    } else if (rez == 't') {
      flags->flag_t = 1;
      flags->flag_v = 1;
    } else if (rez == 'E') {
      flags->flag_e = 1;
      flags->flag_v = 1;
    } else if (rez == 'T') {
      flags->flag_t = 1;
      flags->flag_v = 1;
    } else {
      fprintf(stderr, "found unknown option\n");
      return 1;
    }
    option_index = -1;
  }
  return 0;
}

void working(FILE *file, op flags) {
  char ch = 0;
  char prev = '\n';
  int empty_counter = 0;
  int str_counter = 1;
  while ((ch = getc(file)) != EOF) {
    if (flags.flag_s && ch == '\n' && prev == '\n') {
      empty_counter++;
      if (empty_counter > 1) {
        continue;
      }
    } else {
      empty_counter = 0;
    }
    if (flags.flag_b && flags.flag_n) {
      flags.flag_n = 0;
    }
    if (((flags.flag_b && ch != '\n') || flags.flag_n) && prev == '\n') {
      printf("%6d\t", str_counter++);
    }
    if (ch == '\n' && flags.flag_e) {
      printf("$");
    }
    if (ch == '\t' && flags.flag_t) {
      printf("^I");
    } else if (ch >= 0 && ch < 32 && ch != 9 && ch != 10 && flags.flag_v) {
      printf("^%c", ch + 64);
    } else if (ch == 127 && flags.flag_v) {
      printf("^?");
    } else {
      printf("%c", ch);
    }
    prev = ch;
  }
}