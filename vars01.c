#include "custom_shell.h"

/**
 ** custom_is_chain_del - Test if the current char in the buffer is a chain delimiter
 **
 ** @info: The parameter struct
 ** @buf: The char buffer
 ** @cur_pos: Address of the current position in buf
 **
 ** Return: 1 if chain delimiter, 0 otherwise
 **/
int custom_is_chain_del(info_t *info, char *buf, size_t *cur_pos)
{
	size_t j = *cur_pos;

	if (buf[j] == '|' && buf[j + 1] == '|')
{
	buf[j] = 0;
	j++;
	info->cmd_buf_type = CMD_OR;
}
	else if (buf[j] == '&' && buf[j + 1] == '&')
{
	buf[j] = 0;
	j++;
	info->cmd_buf_type = CMD_AND;
}
	else if (buf[j] == ';')
{
	buf[j] = 0;
	info->cmd_buf_type = CMD_CHAIN;
}
	else
	return (0);

	*cur_pos = j;
	return (1);
}

/**
 ** custom_chain_status - Checks if we should continue chaining based on the last status
 **
 ** @info: The parameter struct
 ** @buf: The char buffer
 ** @cur_pos: Address of the current position in buf
 ** @ist_pos: Starting position in buf
 ** @buf_len: Length of buf
 ** Return: Void
 **/
void custom_chain_status(info_t *info, char *buf, size_t *cur_pos, size_t ist_pos, size_t buf_len)
{
	size_t j = *cur_pos;

	if (info->cmd_buf_type == CMD_AND)
{
	if (info->status)
{
	buf[ist_pos] = 0;
	j = buf_len;
}
}
	if (info->cmd_buf_type == CMD_OR)
{
	if (!info->status)
{
	buf[ist_pos] = 0;
	j = buf_len;
}
}
	*cur_pos = j;
}

/**
 ** custom_replace_alias - Replaces an alias in the tokenized string
 ** @info: The parameter struct
 ** Return: 1 if replaced, 0 otherwise
 **/
int custom_replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
{
	node = custom_node_starts_with(info->alias, info->argv[0], '=');
	if (!node)
	return (0);

	free(info->argv[0]);
	p = _strchr(node->str, '=');
	if (!p)
	return (0);

	p = _strdup(p + 1);
	if (!p)
	return (0);

	info->argv[0] = p;
}
	return (1);
}

/**
 ** custom_replace_vars - Replaces vars in the tokenized string
 **
 ** @info: The parameter struct
 ** Return: 1 if replaced, 0 otherwise
 **/
int custom_replace_vars(info_t *info)
{
	int b;
	list_t *node;

	for (b = 0; info->argv[b]; b++)
{
	if (info->argv[b][0] != '$' || !info->argv[b][1])
	continue;

	if (!_strcmp(info->argv[b], "$?"))
{
	custom_replace_string(&(info->argv[b]), _strdup(custom_convert_number(info->status, 10, 0)));
	continue;
}

	if (!_strcmp(info->argv[b], "$$"))
{
	custom_replace_string(&(info->argv[b]), _strdup(custom_convert_number(getpid(), 10, 0)));
	continue;
}

	node = custom_node_starts_with(info->env, &info->argv[b][1], '=');
	if (node)
{
	custom_replace_string(&(info->argv[b]), _strdup(_strchr(node->str, '=') + 1));
	continue;
}

	custom_replace_string(&info->argv[b], _strdup(""));
}
	return (0);
}

/**
 ** custom_replace_string - Replaces a string
 **
 ** @old: Address of the old string
 ** @new: New string
 **
 ** Return: 1 if replaced, 0 otherwise
 **/
int custom_replace_string(char **old, char *new)
{
	free(*old);

	*old = new;
	return (1);
}
