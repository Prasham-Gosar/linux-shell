#include "shell.h"

int parse_input(char *buffer, char **args)
{
    char *token = strtok(buffer, " ");
    int count = 0;
    int i = 0;

    while (token != NULL)
    {
        args[i] = token;
        token = strtok(NULL, " ");
        count++;
        i++;
    }

    args[i] = NULL;

    return count;
}