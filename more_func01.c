#include "custom_shell.h"

/**
 ** custom_check_builtin - Check if the command is a builtin
 **
 ** @cmd: Command to check
 ** Return: 0 Success, -1 Fail
 **/
int custom_check_builtin(char **cmd)
{
	custom_builtin fun[] = {
	{"cd", NULL},
	{"help", NULL},
	{"echo", NULL},
	{"history", NULL},
	{NULL, NULL}};
	int i = 0;

	if (*cmd == NULL)
{
	return (-1);
}

	while ((fun + i)->command)
{
	if (custom_strcmp(cmd[0], (fun + i)->command) == 0)
	return (0);
	i++;
}
	return (-1);
}

/**
 ** custom_create_environment - Create an array of environment variables
 ** @envi: Array of environment variables
 ** Return: Void
 **/
void custom_create_environment(char **envi)
{
	int i;

	for (i = 0; environ[i]; i++)
	envi[i] = custom_strdup(environ[i]);
	envi[i] = NULL;
}
