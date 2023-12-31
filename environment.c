#include <shell.h>

/**
 ** print_environment - current environment
 ** @info: Structure containing potential
 ** Return: 0
 **/
int print_environment(info_t *info)
{
	if (info == NULL)
{
	fprintf(stderr, "Error: info is NULL\n");
	return (1);
}
	print_list_str(info->env);
	return (0);
}

/**
 ** get_env_var - get  an environment
 ** @info: Structure containing potential
 ** @name: name
 ** Return: value
 **/
char *get_env_var(info_t *info, const char *name)
{
	list_t *node = info->env;
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
	p = starts_with(node->str, name);
	if (p && *p)
	return (p);
	node = node->next;
}
	return (NULL);
}

/**
 ** set_env_var - set a new environment
 ** @info: Structure containing potential
 **  Return: 0 , or 1
 **/
int set_env_var(info_t *info)
{
	if (info == NULL)
{
	fprintf(stderr, "Error: info is NULL\n");
	return (1);
}

	if (info->argc != 3)
{
	_eputs("Incorrect number of arguements\n");
	return (1);
}
	if (_setenv(info, info->argv[1], info->argv[2]))
	return (0);
	return (1);
}

/**
 ** unset_env_var - remove environment
 ** @info: Structure containing potential
 **  Return: 0 , or 1
 **/
int unset_env_var(info_t *info)
{
	int i;

	if (info == NULL)
{
	fprintf(stderr, "Error: info is NULL\n");
	return (1);
}

	if (info->argc == 1)
{
	_eputs("Too few arguements.\n");
	return (1);
}
	for (i = 1; i <= info->argc; i++)
	_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 ** populate_env_list - populates environment
 ** @info: Structure containing potential
 ** Return: 0 , or 1
 **/
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	if (info == NULL)
{
	fprintf(stderr, "Error: info is NULL\n");
	return (1);
}

	for (i = 0; environ[i]; i++)
	add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
