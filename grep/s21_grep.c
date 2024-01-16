#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char string[MAX_SIZE] = {0};
  parser(argc, argv, &flags, string);
  return 0;
}

int parser(int argc, char **argv, op *flags, char *string) {
  const char *short_options = "e:ivclnhsf:o";
  int rez = 0;
  while ((rez = getopt_long(argc, argv, short_options, 0, 0)) != -1) {
    if (rez == 'e') {
      flags->flag_e = 1;
      change_string(string, optarg);
    } else if (rez == 'i') {
      flags->flag_i = 1;
    } else if (rez == 'v') {
      flags->flag_v = 1;
    } else if (rez == 'c') {
      flags->flag_c = 1;
    } else if (rez == 'l') {
      flags->flag_l = 1;
    } else if (rez == 'n') {
      flags->flag_n = 1;
    } else if (rez == 'h') {
      flags->flag_h = 1;
    } else if (rez == 's') {
      flags->flag_s = 1;
    } else if (rez == 'f') {
      flags->flag_f = 1;
      open_file(optarg, string);
    } else if (rez == 'o') {
      flags->flag_o = 1;
    } else {
      printf("found unknown option\n");
      return 1;
    }
  }
  if (!flags->flag_e && !flags->flag_f) {
    string = argv[optind];
    optind++;
  }
  working(string, flags, argc, argv);
  return 0;
}

void working(char *string, op *flags, int argc, char **argv) {
  char arr[MAX_SIZE] = {0};
  int f_counter = 0;
  f_counter = argc - optind;
  for (int i = optind; i < argc; ++i) {
    FILE *file;
    if ((file = fopen(argv[i], "r")) == NULL) {
      if (!flags->flag_s) {
        fprintf(stderr, "не удается открыть файл %s для вывода\n", argv[i]);
      }
      continue;
    }
    strcpy(arr, argv[i]);
    compiling(file, flags, string, arr, f_counter);
    fclose(file);
  }
}

void compiling(FILE *file, op *flags, char *string, char *arr, int f_counter) {
  regex_t re;
  regmatch_t pm[1];
  char line[MAX_SIZE] = {0};
  int reercode = 0;
  int line_counter = 1, coincidences = 0, line_coincidences = 0;
  if (flags->flag_i) {
    reercode = regcomp(&re, string, REG_EXTENDED | REG_ICASE);
    check_compiling(reercode, &re);
  } else {
    reercode = regcomp(&re, string, REG_EXTENDED);
    check_compiling(reercode, &re);
  }
  while (fgets(line, MAX_SIZE - 1, file) != NULL) {
    reercode = regexec(&re, line, 1, pm, 0);
    if (strchr(line, '\n') == NULL) {
      strcat(line, "\n");
    }
    if (reercode == 0 && !flags->flag_v) {
      coincidences = 1;
    }
    if (reercode == REG_NOMATCH && flags->flag_v) {
      coincidences = 1;
    }
    if (f_counter > 1 && !flags->flag_c && !flags->flag_l && !flags->flag_h &&
        coincidences) {
      printf("%s:", arr);
    }
    if (flags->flag_n && coincidences && !flags->flag_c && !flags->flag_l) {
      printf("%d:", line_counter);
    }
    if (flags->flag_o && flags->flag_v) {
      flags->flag_o = 0;
    }
    if (flags->flag_o && coincidences && !flags->flag_c && !flags->flag_l) {
      function_o(string, line, flags);
    }
    if (coincidences && !flags->flag_l && !flags->flag_c && !flags->flag_o) {
      printf("%s", line);
    }
    line_counter++;
    line_coincidences += coincidences;
    coincidences = 0;
  }
  if (flags->flag_c && flags->flag_l) {
    if (line_coincidences > 0) {
      line_coincidences = 1;
    }
  }
  if (flags->flag_c) {
    if (f_counter > 1 && !flags->flag_h) {
      printf("%s:%d\n", arr, line_coincidences);
    } else {
      printf("%d\n", line_coincidences);
    }
  }
  if (flags->flag_l && line_coincidences > 0) {
    printf("%s\n", arr);
  }
  regfree(&re);
}

void check_compiling(int reercode, regex_t *re) {
  char reerbuff[MAX_SIZE] = {0};
  if (reercode != 0) {
    regerror(reercode, re, reerbuff, sizeof(reerbuff));
    fputs(reerbuff, stderr);
    regfree(re);
  }
}

void open_file(char *name, char *string) {
  FILE *f;
  char buffer[MAX_SIZE] = {0};
  if ((f = fopen(name, "r")) != NULL) {
    while (fgets(buffer, MAX_SIZE, f) != NULL) {
      if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
      }
      change_string(string, buffer);
    }
  }
  fclose(f);
}

void change_string(char *string, char *buffer) {
  if (string[0] != 0) {
    strcat(string, "|");
    strcat(string, buffer);
  } else {
    strcat(string, buffer);
  }
}

void function_o(char *string, char *line, op *flags) {
  regex_t rem;
  regmatch_t pm[1];
  char *buf = line;
  int check = 0;

  if (flags->flag_i) {
    check = regcomp(&rem, string, REG_EXTENDED | REG_ICASE);
    check_compiling(check, &rem);
  } else {
    check = regcomp(&rem, string, REG_EXTENDED);
    check_compiling(check, &rem);
  }
  if (check == 0) {
    for (int i = 0; line[i] != '\n'; i++) {
      if ((check = regexec(&rem, buf, 1, pm, 0)) != 0) {
        break;
      }
      printf("%.*s\n", (int)(pm[0].rm_eo - pm[0].rm_so), buf + pm[0].rm_so);
      buf += pm[0].rm_eo;
    }
    regfree(&rem);
  }
}