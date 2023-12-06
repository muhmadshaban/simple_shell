#include "shell.h"
/**
 ** exit_bul -statue shell
 ** @cmd: command
 ** @input: input
 ** @argv:name
 ** @c:Excute count
 ** Return: Void
 **/
void  exit_bul(char **cmd, char *input, char **argv, int c)
{
	int statue, i = 0;

	if (cmd[1] == NULL)
{
	free(input);
	free(cmd);
	exit(EXIT_SUCCESS);
}
	while (cmd[1][i])
{
	if (_isalpha(cmd[1][i++]) != 0)
{
	_prerror(argv, c, cmd);
	break;
}
	else
{
	statue = _atoi(cmd[1]);
	free(input);
	free(cmd);
	exit(statue);
}
}
}

/**
 ** change_dir - cd
 ** @cmd: command
 ** @er: statue last command
 ** Return: 0 , or 1
 **/
int change_dir(char **cmd, __attribute__((unused))int er)
{
	int value = -1;
	char cwd[PATH_MAX];

	if (cmd[1] == NULL)
	value = chdir(getenv("HOME"));
	else if (_strcmp(cmd[1], "-") == 0)
{
	value = chdir(getenv("OLDPWD"));
}
	else
	value = chdir(cmd[1]);

	if (value == -1)
{
	perror("hsh");
	return (-1);
}
	else if (value != -1)
{
	getcwd(cwd, sizeof(cwd));
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
}
	return (0);
}

/**
 ** dis_env - enviroment variable
 ** @cmd:command
 ** @er:statue of last command
 ** Return:0
 **/
int dis_env(__attribute__((unused)) char **cmd, __attribute__((unused)) int er)
{
	size_t i;
	int len;

	for (i = 0; environ[i] != NULL; i++)
{
	len = _strlen(environ[i]);
	write(1, environ[i], len);
	write(STDOUT_FILENO, "\n", 1);
}
	return (0);
}

/**
 ** display_help - displaying help
 ** @cmd:command
 ** @er: statue of last command
 ** Return: 0 , or 1
 **/
int display_help(char **cmd, __attribute__((unused))int er)
{
	int fd, fw, rd = 1;
	char c;

	fd = open(cmd[1], O_RDONLY);
	if (fd < 0)
{
	perror("Error");
	return (0);
}
	while (rd > 0)
{
	rd = read(fd, &c, 1);
	fw = write(STDOUT_FILENO, &c, rd);
	if (fw < 0)
{
	return (-1);
}
}
	_putchar('\n');
	return (0);
}

/**
 ** echo_bul - echo cases
 ** @st:statue last command
 ** @cmd: last command
 ** Return: 0
 **/
int echo_bul(char **cmd, int st)
{
	char *path;
	unsigned int  pid = getppid();

	if (_strncmp(cmd[1], "$?", 2) == 0)
{
	print_number_in(st);
	PRINTER("\n");
}
	else if (_strncmp(cmd[1], "$$", 2) == 0)
{
	print_number(pid);
	PRINTER("\n");

}
	else if (_strncmp(cmd[1], "$PATH", 5) == 0)
{
	path = _getenv("PATH");
	PRINTER(path);
	PRINTER("\n");
	free(path);

}
	else
	return (print_echo(cmd));

	return (1);
}

/**
 ** history_dis - history of user
 ** @c:Parsed Command
 ** @s:Statue Of Last Excute
 ** Return: 0 Succes -1 Fail
 **/
int history_dis(__attribute__((unused))char **c, __attribute__((unused))int s)
{
	char *filename = ".simple_shell_history";
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;
	char *er;

	fp = fopen(filename, "r");
	if (fp == NULL)
{
	return (-1);
}
	while ((getline(&line, &len, fp)) != -1)
{
	counter++;
	er = _itoa(counter);
	PRINTER(er);
	free(er);
	PRINTER(" ");
	PRINTER(line);

}
	if (line)
	free(line);
	fclose(fp);
	return (0);
}

/**
 ** print_echo - normal echi
 ** @cmd: command
 ** Return: 0 , or 1
 **/
int print_echo(char **cmd)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
{
	if (execve("/bin/echo", cmd, environ) == -1)
{
	return (-1);
}
	exit(EXIT_FAILURE);
}
	else if (pid < 0)
{
	return (-1);
}
	else
{
	do {
	waitpid(pid, &status, WUNTRACED);
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
	return (1);
}

/**
 ** print_history - history list
 ** @info: Structure containing potential
 **  Return: 0
 **/
int print_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 ** unset_alias - sets alias
 ** @info: struct
 ** @alias_str: string
 ** Return: 0 , or 1
 **/
int unset_alias(info_t *info, char *alias_str)
{
	char *equal_sign, temp_char;
	int ret;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
	return (1);
	temp_char = *equal_sign;
	*equal_sign = 0;
	ret = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));
	*equal_sign = temp_char;
	return (ret);
}

/**
 ** set_alias - sets alias
 ** @info:  struct
 ** @alias_str: string
 ** Return: 0 ,  or 1
 **/
int set_alias(info_t *info, char *alias_str)
{
	char *equal_sign;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
	return (1);
	if (!*++equal_sign)
	return (unset_alias(info, alias_str));

	unset_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 ** print_alias - prints a string
 ** @node: node
 **
 ** Return: 0, or 1
 **/
int print_alias(list_t *node)
{
	char *equal_sign = NULL, *alias_name = NULL;

	if (node)
{
	equal_sign = _strchr(node->str, '=');
	for (alias_name = node->str; alias_name <= equal_sign; alias_name++)
	_putchar(*alias_name);
	_putchar('\'');
	_puts(equal_sign + 1);
	_puts("'\n");
	return (0);
}
	return (1);
}

/**
 ** print_aliases - (man alias)
 ** @info: Structure containing potential
 **  Return: 0
 **/
int print_aliases(info_t *info)
{
	int i = 0;
	char *equal_sign = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
{
	node = info->alias;
	while (node)
{
	print_alias(node);
	node = node->next;
}
	return (0);
}
	for (i = 1; info->argv[i]; i++)
{
	equal_sign = _strchr(info->argv[i], '=');
	if (equal_sign)
	set_alias(info, info->argv[i]);
	else
	print_alias(node_starts_with(info->alias, info->argv[i], '='));
}

	return (0);
}
