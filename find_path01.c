#include "custom_shell.h"

/**
 ** custom_path_command - Search in $PATH for executable command
 ** @cmd: Parsed input
 ** Return: 1 for failure, 0 for success
 **/
int custom_path_command(char **cmd)
{
	char *path, *value, *cmd_path;
	struct stat buf;

	path = custom_getenv("PATH");
	value = custom_strtok(path, ":");
	while (value != NULL)
{
	cmd_path = custom_build(*cmd, value);
	if (stat(cmd_path, &buf) == 0)
{
	*cmd = custom_strdup(cmd_path);
	free(cmd_path);
	free(path);
	return (0);
}
	free(cmd_path);
	value = custom_strtok(NULL, ":");
}
	free(path);

	return (1);
}

/**
 ** custom_build - Build command
 ** @token: Executable command
 ** @value: Directory containing command
 **
 ** Return: Parsed full path of command or NULL in case of failure
 **/
char *custom_build(char *token, char *value)
{
	char *cmd;
	size_t len;

	len = custom_strlen(value) + custom_strlen(token) + 2;
	cmd = malloc(sizeof(char) * len);
	if (cmd == NULL)
{
	return (NULL);
}

	memset(cmd, 0, len);

	cmd = custom_strcat(cmd, value);
	cmd = custom_strcat(cmd, "/");
	cmd = custom_strcat(cmd, token);

	return (cmd);
}

/**
 ** custom_getenv - Gets the value of environment variable by name
 ** @name: Environment variable name
 ** Return: The value of the environment variable else NULL
 **/
char *custom_getenv(char *name)
{
	size_t nl, vl;
	char *value;
	int i, x, j;

	nl = custom_strlen(name);
	for (i = 0; environ[i]; i++)
{
	if (custom_strncmp(name, environ[i], nl) == 0)
{
	vl = custom_strlen(environ[i]) - nl;
	value = malloc(sizeof(char) * vl);
	if (!value)
{
	free(value);
	perror("unable to alloc");
	return (NULL);
}

	j = 0;
	for (x = nl + 1; environ[i][x]; x++, j++)
{
	value[j] = environ[i][x];
}
	value[j] = '\0';

	return (value);
}
}

	return (NULL);
}
