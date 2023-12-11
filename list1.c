#include <shell.h>

/**
 ** get_list_length - determines length
 **
 ** @head: pointer
 **
 ** Return: list
 **/
size_t get_list_length(const list_t *head)
{
	size_t size = 0;

	while (head)
{
	head = head->next;
	size++;
}
	return (size);
}

/**
 ** list_to_strings - returns an array
 **
 ** @head: pointer
 **
 ** Return: strings
 **/
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = get_string_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
	return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
	return (NULL);

	for (i = 0; node; node = node->next, i++)
{
	str = malloc(str_length(node->str) + 1);
	if (!str)
{
	for (j = 0; j < i; j++)
	free(strs[j]);
	free(strs);
	return (NULL);
}
	str = _strcpy(str, node->str);
	strs[i] = str;
}
	strs[i] = NULL;
	return (strs);
}

/**
 ** print_list - prints all elements
 **
 ** @head: pointer
 **
 ** Return: size of list
 **/
size_t print_list(const list_t *head)
{
	size_t size = 0;

	while (head)
{
	_puts(convert_number(head->num, 10, 0));
	_putchar(':');
	_putchar(' ');
	_puts(head->str ? head->str : "(nil)");
	_puts("\n");
	head = head->next;
	size++;
}
	return (size);
}

/**
 ** node_starts_with - returns node
 **
 ** @node: pointer to list
 **
 ** @prefix: string
 **
 ** @c: the next character
 **
 ** Return: match node
 **/
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *match = NULL;

	while (node)
{
	match = starts_with(node->str, prefix);
	if (match && ((c == -1) || (*match == c)))
	return (node);
	node = node->next;
}
	return (NULL);
}

/**
 ** get_node_index - gets the index
 **
 ** @head: pointer
 **
 ** @node: pointer to the node
 **
 ** Return: index  -1
 **/
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
{
	if (head == node)
	return (index);
	head = head->next;
	index++;
}
	return (-1);
}
