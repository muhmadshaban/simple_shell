#include "shell.h"

/**
 ** get_environment - returns a copy of the string
 ** @info: Structure containing potential arguments
 ** Return: A copy of the rtring
 **/
char **get_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
{
	info->environ = list_to_strings(info->env);
	log_info("Environment changed, updating environment string array");
	info->env_changed = 0;
}

	return (info->environ);
}

/**
 ** unset_env - Remove an environment
 ** @info: Structure containing potential arguments
 ** Return: 1 or , 0
 ** @env_var: the string
 **/
int unset_env(info_t *info, char *env_var)
{
	list_t *node = info->env;
	size_t index = 0;
	char *env_var_value;

	if (!node || !env_var)
{
	fprintf(stderr, "Error: invalid arguments passed to unset_env\n");
	return (0);
}

	while (node)
{
	env_var_value = starts_with(node->str, env_var);
	if (env_var_value && *env_var_value == '=')
{
	info->env_changed = delete_node_at_index(&(info->env), index);
	index = 0;
	node = info->env;
	continue;
}
	node = node->next;
	index++;
}
	return (info->env_changed);
}

/**
 ** set_environment_variable - Initialize a new environment
 ** @info: Structure containing potential argument
 ** @variable: the string
 ** @value: the string env var value
 **  Return: 0 or 1
 **/
int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
{
	printf("Error: variable or value is NULL\n");
	return (1);
}

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
{
	printf("Error: failed to allocate memory for buffer\n");
	return (1);
}
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
{
	p = starts_with(node->str, variable);
	if (p && *p == '=')
{
	free(node->str);
	node->str = buffer;
	info->env_changed = 1;
	return (0);
}
	node = node->next;
}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
