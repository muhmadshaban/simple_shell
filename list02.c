#include "custom_shell.h"

/**
 ** custom_get_list_length - determines length of linked list
 ** @head: pointer to first node
 ** Return: size of list
 **/
size_t custom_get_list_length(const list_t *head)
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
 ** custom_list_to_strings - returns an array of strings of the list->str
 ** @head: pointer to first node
 ** Return: array of strings
 **/
char **custom_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = custom_get_string_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
	return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
	return (NULL);

	for (i = 0; node; node = node->next, i++)
{
	str = malloc(custom_str_length(node->str) + 1);
	if (!str)
{
	for (j = 0; j < i; j++)
	free(strs[j]);
	free(strs);
	return (NULL);
}
	str = custom_strcpy(str, node->str);
	strs[i] = str;
}
	strs[i] = NULL;
	return (strs);
}

/**
 ** custom_print_list - prints all elements of a list_t linked list
 ** @head: pointer to first node
 ** Return: size of list
 **/
size_t custom_print_list(const list_t *head)
{
	size_t size = 0;

	while (head)
{
	custom_puts(custom_convert_number(head->num, 10, 0));
	custom_putchar(':');
	custom_putchar(' ');
	custom_puts(head->str ? head->str : "(nil)");
	custom_puts("\n");
	head = head->next;
	size++;
}
	return (size);
}

/**
 ** custom_node_starts_with - returns node whose string starts with prefix
 ** @node: pointer to list head
 ** @prefix: string to match
 ** @c: the next character after prefix to match
 ** Return: match node or null
 **/
list_t *custom_node_starts_with(list_t *node, char *prefix, char c)
{
	char *match = NULL;

	while (node)
{
	match = custom_starts_with(node->str, prefix);
	if (match && ((c == -1) || (*match == c)))
	return (node);
	node = node->next;
}
	return (NULL);
}

/**
 ** custom_get_node_index - gets the index of a node
 ** @head: pointer to list head
 ** @node: pointer to the node
 ** Return: index of node or -1
 **/
ssize_t custom_get_node_index(list_t *head, list_t *node)
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
