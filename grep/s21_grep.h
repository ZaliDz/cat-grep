#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 4096

typedef struct flags {
  int flag_e;
  int flag_i;
  int flag_v;
  int flag_c;
  int flag_l;
  int flag_n;
  int flag_h;
  int flag_f;
  int flag_s;
  int flag_o;
} op;
op flags = {0};

void compiling(FILE *file, op *flags, char *string, char *arr, int f_counter);
void check_compiling(int reercode, regex_t *re);
void open_file(char *name, char *string);
int parser(int argc, char **argv, op *flags, char *string);
void function_o(char *string, char *line, op *flags);
void working(char *string, op *flags, int argc, char **argv);
void change_string(char *string, char *buffer);

#endif