#include "custom_shell.h"

/**
 ** custom_get_environment - returns a copy of the environment string array
 ** @info: Structure containing potential arguments. Used to maintain
 ** a constant function prototype.
 ** Return: A copy of the environment string array
 **/
char **custom_get_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
{
	info->environ = custom_list_to_strings(info->env);
	custom_log_info("Environment changed, updating environment string array");
	info->env_changed = 0;
}

	return (info->environ);
}

/**
 ** custom_unset_environment - Remove an environment variable
 **
 ** @info: Structure containing potential arguments. Used to maintain
 ** a constant function prototype.
 **
 ** Return: 1 on delete, 0 otherwise
 **
 ** @env_var: the string env var property
 **/
int custom_unset_environment(info_t *info, char *env_var)
{
	list_t *node = info->env;
	size_t index = 0;
	char *env_var;

	if (!node || !env_var)
{
	fprintf(stderr, "Error: invalid arguments passed to custom_unset_environment\n");
	return (0);
}

	while (node)
{
	env_var = custom_starts_with(node->str, env_var);
	if (env_var && *env_var == '=')
{
	info->env_changed = custom_delete_node_at_index(&(info->env), index);
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
 ** custom_set_environment_variable - Initialize a new environment variable,
 ** or modify an existing one
 ** @info: Structure containing potential arguments. Used to maintain
 ** a constant function prototype.
 ** @variable: the string env var property
 ** @value: the string env var value
 ** Return: 0 on success, 1 on failure
 **/
int custom_set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
{
	custom_printf("Error: variable or value is NULL\n");
	return (1);
}

	buffer = custom_malloc(custom_strlen(variable) + custom_strlen(value) + 2);
	if (!buffer)
{
	custom_printf("Error: failed to allocate memory for buffer\n");
	return (1);
}
	custom_strcpy(buffer, variable);
	custom_strcat(buffer, "=");
	custom_strcat(buffer, value);
	node = info->env;
	while (node)
{
	p = custom_starts_with(node->str, variable);
	if (p && *p == '=')
{
	custom_free(node->str);
	node->str = buffer;
	info->env_changed = 1;
	return (0);
}
	node = node->next;
}
	custom_add_node_end(&(info->env), buffer, 0);
	custom_free(buffer);
	info->env_changed = 1;
	return (0);
}
