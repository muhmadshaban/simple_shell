#include "custom_shell.h"

/**
 ** display_command_history - Display the history list, one command per line, preceded
 ** w ith line numbers, starting at 0.
 ** @info: Structure containing potential arguments. Used to maintain
 ** constant function prototype.
 ** Return: Always 0
 **/
int display_command_history(info_t *info)
{
	display_list(info->command_history);
	return (0);
}

/**
 ** clear_alias - Clear an alias
 ** @info: Parameter structure
 ** @alias_string: The alias string
 **
 ** Return: Always 0 on success, 1 on error
 **/
int clear_alias(info_t *info, char *alias_string)
{
	char *equal_sign, temp_char;
	int result;

	equal_sign = _strchr(alias_string, '=');
	if (!equal_sign)
	return (1);
	temp_char = *equal_sign;
	*equal_sign = 0;
	result = remove_node_at_index(&(info->aliases),
	get_node_index(info->aliases, node_starts_with(info->aliases, alias_string, -1)));
	*equal_sign = temp_char;
	return (result);
}

/**
 ** create_alias - Create an alias
 ** @info: Parameter structure
 ** @alias_string: The alias string
 **
 ** Return: Always 0 on success, 1 on error
 **/
int create_alias(info_t *info, char *alias_string)
{
	char *equal_sign;

	equal_sign = _strchr(alias_string, '=');
	if (!equal_sign)
	return (1);
	if (!*++equal_sign)
	return (clear_alias(info, alias_string));

	clear_alias(info, alias_string);
	return (add_node_end(&(info->aliases), alias_string, 0) == NULL);
}

/**
 ** print_alias_command - Print an alias command
 ** @node: The alias node
 **
 ** Return: Always 0 on success, 1 on error
 **/
int print_alias_command(list_t *node)
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
 ** display_aliases - Display aliases, similar to the 'alias' command
 ** @info: Structure containing potential arguments. Used to maintain
 ** constant function prototype.
 ** Return: Always 0
 **/
int display_aliases(info_t *info)
{
	int i = 0;
	char *equal_sign = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
{
	node = info->aliases;
	while (node)
{
	print_alias_command(node);
	node = node->next;
}
	return (0);
}
	for (i = 1; info->argv[i]; i++)
{
	equal_sign = _strchr(info->argv[i], '=');
	if (equal_sign)
	create_alias(info, info->argv[i]);
	else
	print_alias_command(node_starts_with(info->aliases, info->argv[i], '='));
}

	return (0);
}
