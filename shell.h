#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int shell_loop(const char *prog, char **envp);

void trim_line(char *s);
int run_one_word(const char *prog, unsigned long line_no, char *cmd, char **envp);

void print_not_found(const char *prog, unsigned long line_no, const char *cmd);

#endif
