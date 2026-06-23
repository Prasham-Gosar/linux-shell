#include "shell.h"

void handle_pipe(char **args, int argc)
{
    int pipe_index = -1;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(args[i], "|") == 0)
        {
            pipe_index = i;
            break;
        }
    }

    if (pipe_index == -1)
    {
        return;
    }

    if (pipe_index == 0)
    {
        printf("Error: missing command before |\n");
        return;
    }

    if (pipe_index == argc - 1)
    {
        printf("Error: missing command after |\n");
        return;
    }

    args[pipe_index] = NULL;

    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid_t pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);

        execvp(args[0], args);

        perror(args[0]);
        exit(1);
    }

    pid_t pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);

        close(fd[0]);
        close(fd[1]);

        execvp(args[pipe_index + 1], &args[pipe_index + 1]);

        perror(args[pipe_index + 1]);
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void handle_redirection(char **args, int *argc)
{
    for (int i = 0; i < *argc; i++)
    {
        if (strcmp(args[i], ">") == 0)
        {
            if (i + 1 < *argc)
            {
                int fd = open(args[i + 1],
                              O_WRONLY | O_CREAT | O_TRUNC,
                              0644);

                if (fd < 0)
                {
                    perror("open");
                    exit(1);
                }

                dup2(fd, STDOUT_FILENO);
                close(fd);

                args[i] = NULL;
                *argc = i;
            }
            else
            {
                printf("Error: No output file specified\n");
                exit(1);
            }
        }
        else if (strcmp(args[i], ">>") == 0)
        {
            if (i + 1 < *argc)
            {
                int fd = open(args[i + 1],
                              O_WRONLY | O_CREAT | O_APPEND,
                              0644);

                if (fd < 0)
                {
                    perror("open");
                    exit(1);
                }

                dup2(fd, STDOUT_FILENO);
                close(fd);

                args[i] = NULL;
                *argc = i;
            }
            else
            {
                printf("Error: No output file specified\n");
                exit(1);
            }
        }
        else if (strcmp(args[i], "<") == 0)
        {
            if (i + 1 < *argc)
            {
                int fd = open(args[i + 1], O_RDONLY);

                if (fd < 0)
                {
                    perror("open");
                    exit(1);
                }

                dup2(fd, STDIN_FILENO);
                close(fd);

                args[i] = NULL;
                *argc = i;
            }
            else
            {
                printf("Error: No input file specified\n");
                exit(1);
            }
        }
    }
}

void execute_command(char **args, int argc, int background)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return;
    }

    if (pid == 0)
    {
        handle_redirection(args, &argc);

        execvp(args[0], args);

        perror(args[0]);
        exit(1);
    }
    else
    {
        if (!background)
        {
            wait(NULL);
        }
    }
}