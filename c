opy code
#include "custom_shell.h"

/**
 * custom_handle_builtin - Handle Builtin Command
 * @cmd: Parsed Command
 * @er: Status of the last execution
 * Return: -1 (Fail), 0 (Success) (Return: Execute Builtin)
 */
int custom_handle_builtin(char **cmd, int er)
{
    builtin custom_builtins[] = {
        {"cd", custom_change_directory},
        {"env", custom_display_environment},
        {"help", custom_display_help},
        {"echo", custom_echo},
        {"history", custom_display_history},
        {NULL, NULL}
    };
    int i = 0;

    while (custom_builtins[i].command)
    {
        if (_custom_strcmp(cmd[0], custom_builtins[i].command) == 0)
        {
            return (custom_builtins[i].fun(cmd, er)); // Added parentheses
        }
        i++;
    }
    return (-1); // Added parentheses
}

/**
 * custom_execute_command - Execute Simple Shell Command (Fork, Wait, Execute)
 *
 * @cmd: Parsed Command
 * @input: User Input
 * @c: Shell Execution Time (in case of Command Not Found)
 * @argv: Program Name
 * Return: 1 if Command is NULL, -1 for Wrong Command, 0 if Command Executed
 */
int custom_execute_command(char **cmd, char *input, int c, char **argv)
{
    int status;
    pid_t pid;

    if (*cmd == NULL)
    {
        return 1;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Error");
        return -1;
    }

    if (pid == 0)
    {
        if (_custom_strncmp(*cmd, "./", 2) != 0 && _custom_strncmp(*cmd, "/", 1) != 0)
        {
            custom_path_command(cmd);
        }

        if (execve(*cmd, cmd, environ) == -1)
        {
            custom_print_error(cmd[0], c, argv);
            free(input);
            free(cmd);
            exit(EXIT_FAILURE);
        }
        return EXIT_SUCCESS;
    }
    wait(&status);
    return 0;
}

/**
 * custom_signal_handler - Handle SIGINT (Ctrl+C)
 * @sig: Captured Signal
 * Return: Void
 */
void custom_signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        custom_printer("\n$ ");
    }
}
