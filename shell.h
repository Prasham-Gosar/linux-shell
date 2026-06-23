#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

int parse_input(char *buffer, char **args);
int handle_builtin(char **args, int argc);
void execute_command(char **args, int argc, int background);
void handle_redirection(char **args, int *argc);
void handle_pipe(char **args, int argc);

#define HISTORY_SIZE 100

extern char *history[HISTORY_SIZE];
extern int history_count;

void add_history(char *input);
void print_history();

#endif