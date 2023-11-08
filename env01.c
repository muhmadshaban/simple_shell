#include "custom_shell.h"

/**
 ** print_custom_environment - prints the current custom environment
 ** @info: Structure containing potential arguments. Used to maintain
 **        constant function prototype.
 ** Return: Always 0
 **/
int print_custom_environment(info_t *info)
{
	if (info == NULL)
{
	fprintf(stderr, "Error: info is NULL\n");
	return (1);
}
	print_custom_list_str(info->custom_env);
	return (0);
}

/**
 ** get_custom_env_var - gets the value of a custom environment variable
 ** @info: Structure containing potential arguments. Used to maintain
 ** @name: custom env var name
 **
 ** Return: the value
 **/
char *get_custom_env_var(info_t *info, const char *name)
{
	list_t *node = info->custom_env;
	char *p;

	if (info == NULL)
{
	fprintf(stderr, "Error: info is NULL\n");
	return (NULL);
}

	if (name == NULL)
{
	fprintf(stderr, "Error: name is NULL\n");
	return (NULL);
}

	while (node)
{
	p = custom_starts_with(node->str, name);
	if (p && *p)
	return (p);
	node = node->next;
}
	return (NULL);
}

/**
 ** set_custom_env_var - Initialize a new custom environment variable,
 **             or modify an existing one
 ** @info: Structure containing potential arguments. Used to maintain
 **        constant function prototype.
 **  Return: 0 on success, 1 on failure
 **/
int set_custom_env_var(info_t *info)
{
	if (info == NULL)
{
	fprintf(stderr, "Error: info is NULL\n");
	return (1);
}

	if (info->argc != 3)
{
	_eputs("Incorrect number of arguments\n");
	return (1);
}
	if (custom_setenv(info, info->argv[1], info->argv[2]))
	return (0);
	return (1);
}

/**
 ** unset_custom_env_var - Remove a custom environment variable
 ** @info: Structure containing potential arguments. Used to maintain
 **        constant function prototype.
 **  Return: 0 on success, 1 on failure
 **/
int unset_custom_env_var(info_t *info)
{
	int i;

	if (info == NULL)
{
	fprintf(stderr, "Error: info is NULL\n");
	return (1);
}

	if (info->argc == 1)
{
	_eputs("Too few arguments.\n");
	return (1);
}
	for (i = 1; i <= info->argc; i++)
	custom_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 ** populate_custom_env_list - populates custom environment linked list
 ** @info: Structure containing potential arguments. Used to maintain
 ** constant function prototype.
 ** Return: 0 on success, 1 on failure
 **/
int populate_custom_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	if (info == NULL)
{
	fprintf(stderr, "Error: info is NULL\n");
	return (1);
}

	for (i = 0; custom_environ[i]; i++)
	add_custom_node_end(&node, custom_environ[i], 0);
	info->custom_env = node;
	return (0);
}
