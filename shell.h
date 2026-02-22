#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int shell_loop(const char *prog, char **envp);

char **split_line(char *line);
void free_argv(char **argv);

char *get_env(const char *name, char **envp);
char *resolve_path(const char *cmd, char **envp);

int exec_cmd(char **av, const char *prog, unsigned long line_no, char **envp);
void print_not_found(const char *prog, unsigned long line_no, const char *cmd);

void print_env(char **envp);

#endif
