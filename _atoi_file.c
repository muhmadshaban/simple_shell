#include <shell.h>

/**
 ** is_interactive - shell is interactive mode
 ** @info: address
 **
 ** Return: 1 or, 0
 **/
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 ** is_delimiter -  character
 ** @c: the char
 ** @delim: string
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
 ** is_alphabetic - alphabetic character
 ** @c: character
 ** Return: 1 orc, 0
 **/

int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	return (1);
	else
	return (0);
}

/**
 ** string_to_int - string to an integer
 ** @s: the string
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
