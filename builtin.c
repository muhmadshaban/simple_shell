#include <shell.h>
/**
 ** history_dis - history of user
 ** @c:Parsed Command
 ** @s:Statue Of Last Excute
 ** Return: 0 Succes -1 Fail
 **/
int history_dis(_attribute((unused))char **c, __attribute_((unused))int s)
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
