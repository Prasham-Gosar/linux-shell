#include "shell.h"

int main()
{
    signal(SIGCHLD, SIG_IGN);
    char buffer[1024];

    while (1)
    {
        printf("myshell> ");

        if (fgets(buffer, 1024, stdin) == NULL)
        {
            printf("\nGoodbye!\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        char *args[100];

        int argc = parse_input(buffer, args);

        if (argc == 0)
        {
            continue;
        }

        add_history(buffer);

        int has_pipe = 0;

        int background = 0;

        if (argc > 0 && strcmp(args[argc - 1], "&") == 0)
        {
            background = 1;
            args[argc - 1] = NULL;
            argc--;
        }

        for (int i = 0; i < argc; i++)
        {
            if (strcmp(args[i], "|") == 0)
            {
                has_pipe = 1;
                break;
            }
        }

        if (has_pipe)
        {
            handle_pipe(args, argc);
        }
        else if (!handle_builtin(args, argc))
        {
            execute_command(args, argc, background);
        }
    }

    return 0;
}