#include "shell.h"

/**
 ** is_interactive - returns true if interactive
 ** @info: struct location
 **
 ** Return: 1 or , 0
 **/
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 ** is_delimiter - checks the character
 ** @c: the new char
 ** @delim: the delimeter
 ** Return: 1 or, 0
 **/
int is_delimiter(char c, char *delim)
{
	while (*delim)
	if (*delim++ == c)
	return (1);
	return (0);
}

/**
 ** is_alphabetic - checks for alphabetic
 ** @c: The input
 ** Return: 1 or, 0
 **/

int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	return (1);
	else
	return (0);
}

/**
 ** string_to_int - converts a string
 ** @s: the new string
 ** Return: 0
 **/

int string_to_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
{
	if (s[i] == '-')
	sign *= -1;

	if (s[i] >= '0' && s[i] <= '9')
{
	flag = 1;
	result *= 10;
	result += (s[i] - '0');
}
	else if (flag == 1)
	flag = 2;
}

	if (sign == -1)
	output = -result;
	else
	output = result;

	return (output);
}