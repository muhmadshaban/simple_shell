#include "custom_shell.h"
/**
 ** exit_shell - Exit the shell with a given status
 ** @cmd: Parsed Command
 ** @input: User Input
 ** @argv: Program Name
 ** @c: Execute Count
 ** Return: Void (Exit Status)
 **/
void exit_shell(char **cmd, char *input, char **argv, int c)
{
	int status, i = 0;

	if (cmd[1] == NULL)
{
	free(input);
	free(cmd);
	exit(EXIT_SUCCESS);
}
	while (cmd[1][i])
{
	if (_is_alphabetic(cmd[1][i++]) != 0)
{
	_print_error(argv, c, cmd);
	break;
}
	else
{
	status = _atoi(cmd[1]);
	free(input);
	free(cmd);
	exit(status);
}
}
}

/**
 ** change_directory - Change the current working directory
 ** @cmd: Parsed Command
 ** @er: Status of the last command executed
 ** Return: 0 Success, 1 Failed (For Old Pwd Always 0, Case No Old PWD)
 **/
int change_directory(char **cmd, __attribute__((unused))int er)
{
	int result = -1;
	char cwd[PATH_MAX];

	if (cmd[1] == NULL)
	result = chdir(getenv("HOME"));
	else if (_strcmp(cmd[1], "-") == 0)
{
	result = chdir(getenv("OLDPWD"));
}
	else
	result = chdir(cmd[1]);

	if (result == -1)
{
	perror("custom_shell");
	return (-1);
}
	else if (result != -1)
{
	getcwd(cwd, sizeof(cwd));
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
}
	return (0);
}
