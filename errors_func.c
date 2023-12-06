#include "shell.h"

/**
 ** _eputs - input string
 ** @str: new string
 ** return : nothing
 **/
void _eputs(char *str)
{
	int i = 0;

	if (!str)
{
	fprintf(stderr, "Error: _eputs() called with NULL string\n");
	return;
}
	while (str[i] != '\0')
{
	_eputchar(str[i]);
	i++;
}
}

/**
 ** _eputchar - character
 ** @c: new character
 **
 ** Return: 1 , or -1
 **/
int _eputchar(char c)
{
	static int buf_index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buf_index >= WRITE_BUF_SIZE)
{
	write(STDERR_FILENO, buf, buf_index);
	buf_index = 0;
}
	if (c != BUF_FLUSH)
	buf[buf_index++] = c;
	return (1);
}

/**
 ** _putfd - character
 ** @c: new character
 ** @fd: filedescriptor
 **
 ** Return: 1 ,or -1
 **/
int _putfd(char c, int fd)
{
	static int buf_index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buf_index >= WRITE_BUF_SIZE)
{
	write(fd, buf, buf_index);
	buf_index = 0;
}
	if (c != BUF_FLUSH)
	buf[buf_index++] = c;
	return (1);
}

/**
 **_putsfd - input string
 ** @str: new string
 ** @fd: filedescriptor
 **
 ** Return: number of chars
 **/
int _putsfd(char *str, int fd)
{
	int char_count = 0;

	if (!str)
{
	fprintf(stderr, "Error: _putsfd() called with NULL string\n");
	return (0);
}
	while (*str)
{
	char_count += _putfd(*str++, fd);
}
	return (char_count);
}
/**
 ** _erratoi - converts a string to an integer
 ** @s: new string
 ** Return: 0 , or -1
 **/
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
	s++;
	for (i = 0;  s[i] != '\0'; i++)
{
	if (s[i] >= '0' && s[i] <= '9')
{
	result *= 10;
	result += (s[i] - '0');
	if (result > INT_MAX)
{
	fprintf(stderr, "Error: Integer overflow\n");
	return (-1);
}
}
	else
{
	fprintf(stderr, "Error: Invalid character in string\n");
	return (-1);
}
}
	return (result);
}

/**
 ** print_error - prints an error message
 ** @info: the parameter
 ** @estr: string containing specified error type
 ** Return: 0 , or -1
 **/
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 ** print_d - print a decimal
 ** @input: input
 ** @fd: filedescriptor
 **
 ** Return: number of character
 **/
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
	__putchar = _eputchar;
	if (input < 0)
{
	_abs_ = -input;
	__putchar('-');
	count++;
}
	else
	_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
{
	if (_abs_ / i)
{
	__putchar('0' + current / i);
	count++;
}
	current %= i;
}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 ** convert_number - converter
 ** @num: number
 ** @base: base
 ** @flags: flags
 **
 ** Return: string
 **/
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
	n = -num;
	sign = '-';

}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
	*--ptr = array[n % base];
	n /= base;
	} while (n != 0);

	if (sign)
	*--ptr = sign;
	return (ptr);
}

/**
 ** remove_comments - replaces first instance
 ** @buf: address
 **
 ** Return: 0
 **/
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
	buf[i] = '\0';
	break;
}
}
