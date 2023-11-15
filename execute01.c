#include "custom_shell.h"

/**
 ** custom_handle_builtin - Handle Builtin Command
 **
 ** @cmd: Parsed Command
 ** @er: Status of last Execute
 **
 ** Return: -1 Fail 0 Success (Return: Execute Builtin)
 **/
int custom_handle_builtin(char **cmd, int er)
{
	custom_builtin bil[] = {
	{"cd", custom_change_dir},
	{"env", custom_dis_env},
	{"help", custom_display_help},
	{"echo", custom_echo_bul},
	{"history", custom_history_dis},
	{NULL, NULL}};

	int i = 0;

	while ((bil + i)->command)
{
	if (custom_strcmp(cmd[0], (bil + i)->command) == 0)
{
	return ((bil + i)->fun(cmd, er));
}
	i++;
}
	return (-1);
}

/**
 ** custom_check_cmd - Execute Simple Shell Command (Fork, Wait, Execute)
 **
 ** @cmd: Parsed Command
 ** @input: User Input
 ** @c: Shell Execution Time Case of Command Not Found
 ** @argv: Program Name
 **
 ** Return: 1 Case Command Null -1 Wrong Command 0 Command Executed
 **/
int custom_check_cmd(char **cmd, char *input, int c, char **argv)
{
	int status;
	pid_t pid;

	if (*cmd == NULL)
{
	return (-1);
}

	pid = fork();
	if (pid == -1)
{
	perror("Error");
	return (-1);
}

	if (pid == 0)
{
	if (custom_strncmp(*cmd, "./", 2) != 0 && custom_strncmp(*cmd, "/", 1) != 0)
{
	custom_path_cmd(cmd);
}

	if (execve(*cmd, cmd, custom_environ) == -1)
{
	custom_print_error(cmd[0], c, argv);
	free(input);
	free(cmd);
	exit(EXIT_FAILURE);
}
	return (EXIT_SUCCESS);
}
	wait(&status);
	return (0);
}

/**
 ** custom_signal_to_handle - Handle ^C
 **
 ** @sig: Captured Signal
 **
 ** Return: Void
 **/
void custom_signal_to_handle(int sig)
{
	if (sig == SIGINT)
{
	custom_PRINTER("\n$ ");
}
}
