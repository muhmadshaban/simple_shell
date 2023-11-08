#include "custom_shell.h"

/**
 ** _custom_eputs - prints an input string to stderr
 ** @str: the string to be printed
 **
 ** Return: Nothing
 **/
void _custom_eputs(char *str)
{
	int i = 0;

	if (!str)
{
	fprintf(stderr, "Error: _custom_eputs() called with NULL string\n");
	return;
}
	while (str[i] != '\0')
{
	_custom_eputchar(str[i]);
	i++;
}
}

/**
 ** _custom_eputchar - writes the character c to stderr
 ** @c: The character to print
 **
 ** Return: On success 1.
 ** On error, -1 is returned, and errno is set appropriately.
 **/
int _custom_eputchar(char c)
{
	static int buf_index;
	static char buf[CUSTOM_WRITE_BUF_SIZE];

	if (c == CUSTOM_BUF_FLUSH || buf_index >= CUSTOM_WRITE_BUF_SIZE)
{
	write(STDERR_FILENO, buf, buf_index);
	buf_index = 0;
}
	if (c != CUSTOM_BUF_FLUSH)
	buf[buf_index++] = c;
	return (1);
}

/**
 ** _custom_putfd - writes the character c to given fd
 ** @c: The character to print
 ** @fd: The filedescriptor to write to
 **
 ** Return: On success 1.
 ** On error, -1 is returned, and errno is set appropriately.
 **/
int _custom_putfd(char c, int fd)
{
	static int buf_index;
	static char buf[CUSTOM_WRITE_BUF_SIZE];

	if (c == CUSTOM_BUF_FLUSH || buf_index >= CUSTOM_WRITE_BUF_SIZE)
{
	write(fd, buf, buf_index);
	buf_index = 0;
}
	if (c != CUSTOM_BUF_FLUSH)
	buf[buf_index++] = c;
	return (1);
}

/**
 ** _custom_putsfd - prints an input string to given fd
 ** @str: the string to be printed
 ** @fd: the filedescriptor to write to
 **
 ** Return: the number of chars put
 **/
int _custom_putsfd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
{
	fprintf(stderr, "Error: _custom_putsfd() called with NULL string\n");
	return (0);
}
	while (*str)
{
	char_count += _custom_putfd(*str++, fd);
}
	return (char_count);
}
