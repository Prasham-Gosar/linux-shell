#include "shell.h"

char *history[HISTORY_SIZE];
int history_count = 0;

void add_history(char *input)
{
    if (history_count < HISTORY_SIZE)
    {
        history[history_count] = strdup(input);
        history_count++;
    }
}

void print_history()
{
    for (int i = 0; i < history_count; i++)
    {
        printf("%d %s\n", i + 1, history[i]);
    }
}

int handle_builtin(char **args, int argc)
{
    if (strcmp(args[0], "cd") == 0)
    {
        if (argc < 2)
        {
            printf("cd: missing argument\n");
        }
        else if (argc > 2)
        {
            printf("cd: too many arguments\n");
        }
        else
        {
            if (chdir(args[1]) != 0)
            {
                perror("cd");
            }
        }

        return 1;
    }

    else if (strcmp(args[0], "pwd") == 0)
    {
        char cwd[1024];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
        }
        else
        {
            perror("pwd");
        }

        return 1;
    }

    else if (strcmp(args[0], "history") == 0)
    {
        print_history();
        return 1;
    }

    else if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }

    return 0;
}