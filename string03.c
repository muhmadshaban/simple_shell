#include "custom_shell.h"

/**
 ** custom_isalpha - Check if alphabetic
 ** @c: Character
 ** Return: 1 if true, 0 if not
 **/
int custom_isalpha(int c)
{
	if (((c >= 97) && (c <= 122)) || ((c >= 65) && (c <= 90)))
{
	return (1);
}
	else
{
	return (0);
}
}

/**
 ** custom_itoa - Convert integer to char
 ** @n: Int to convert
 ** Return: Char pointer
 **/
char *custom_itoa(unsigned int n)
{
	int len = 0, i = 0;
	char *s;

	len = custom_intlen(n);
	s = malloc(len + 1);

	if (!s)
	return (NULL);

	*s = '\0';
	while (n / 10)
{
	s[i] = (n % 10) + '0';
	n /= 10;
	i++;
}

	s[i] = (n % 10) + '0';
	custom_array_rev(s, len);
	s[i + 1] = '\0';

	return (s);
}

/**
 ** custom_array_rev - Reverse array
 ** @arr: Array to reverse
 ** @len: Length of array
 ** Return: Void (Reverse array)
 **/
void custom_array_rev(char *arr, int len)
{
	int i;
	char tmp;

	for (i = 0; i < (len / 2); i++)
{
	tmp = arr[i];
	arr[i] = arr[(len - 1) - i];
	arr[(len - 1) - i] = tmp;
}
}

/**
 ** custom_intlen - Determine length of int
 ** @num: Given int
 ** Return: Length of int
 **/
int custom_intlen(int num)
{
	int len = 0;

	while (num != 0)
{
	len++;
	num /= 10;
}

	return (len);
}

/**
 ** custom_prerror - Print custom error
 ** @argv: Program name
 ** @c: Error count
 ** @cmd: Command
 ** Return: Void
 **/
void custom_prerror(char **argv, int c, char **cmd)
{
	char *er = custom_itoa(c);

	custom_PRINTER(argv[0]);
	custom_PRINTER(": ");
	custom_PRINTER(er);
	custom_PRINTER(": ");
	custom_PRINTER(cmd[0]);
	custom_PRINTER(": Illegal number: ");
	custom_PRINTER(cmd[1]);
	custom_PRINTER("\n");
	free(er);
}
