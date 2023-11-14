#include "custom_shell.h"

/**
 ** custom_print_unsigned_number - Print unsigned int putchar
 ** @n: Unsigned integer
 **
 ** Return: Void
 **/
void custom_print_unsigned_number(unsigned int n)
{
	unsigned int x = n;

	if ((x / 10) > 0)
	custom_print_unsigned_number(x / 10);

	custom_putchar(x % 10 + '0');
}

/**
 ** custom_print_number - Print number putchar
 ** @n: Integer
 **
 ** Return: Void
 **/
void custom_print_number(int n)
{
	unsigned int x = n;

	if (n < 0)
{
	custom_putchar('-');
	x = -x;
}
	if ((x / 10) > 0)
	custom_print_unsigned_number(x / 10);

	custom_putchar(x % 10 + '0');
}

/**
 ** custom_check_delim - Checks if a character matches any char in string
 ** @c: Character to check
 ** @str: String to check
 **
 ** Return: 1 Success, 0 Failed
 **/
unsigned int custom_check_delim(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
{
	if (c == str[i])
	return (1);
}
	return (0);
}

/**
 ** custom_strtok - Tokenize a string (strtok)
 ** @str: String
 ** @delim: Delimiter
 **
 ** Return: Pointer to the next token or NULL
 **/
char *custom_strtok(char *str, const char *delim)
{
	static char *ts;
	static char *nt;
	unsigned int i;

	if (str != NULL)
	nt = str;
	ts = nt;

	if (ts == NULL)
	return (NULL);

	for (i = 0; ts[i] != '\0'; i++)
{
	if (custom_check_delim(ts[i], delim) == 0)
	break;
}

	if (nt[i] == '\0' || nt[i] == '#')
{
	nt = NULL;
	return (NULL);
}

	ts = nt + i;
	nt = ts;

	for (i = 0; nt[i] != '\0'; i++)
{
	if (custom_check_delim(nt[i], delim) == 1)
	break;
}

	if (nt[i] == '\0')
	nt = NULL;
	else
{
	nt[i] = '\0';
	nt = nt + i + 1;

	if (*nt == '\0')
	nt = NULL;
}

	return (ts);
}
