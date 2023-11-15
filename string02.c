#include "custom_shell.h"

/**
 ** custom_strcpy - Copy source to destination char
 ** @dest: Destination
 ** @src: Source
 ** Return: Copy of char *
 **/
char *custom_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
{
	dest[i] = src[i];
	i++;
}
	dest[i] = '\0';
	return (dest);
}

/**
 ** custom_strcat - Concatenate two strings
 ** @dest: First string
 ** @src: Second string
 ** Return: First string + Second string char *
 **/
char *custom_strcat(char *dest, char *src)
{
	char *s = dest;

	while (*dest != '\0')
{
	dest++;
}

	while (*src != '\0')
{
	*dest = *src;
	dest++;
	src++;
}
	*dest = '\0';
	return (s);
}

/**
 ** custom_strchr - Locate character in string
 ** @s: String to search in
 ** @c: Char to search for
 ** Return: Pointer to char *
 **/
char *custom_strchr(char *s, char c)
{
	do

{

	if (*s == c)
{
	break;
}

	} while (*s++);

	return (s);
}

/**
 ** custom_strncmp - Compare amount (n) of characters of two strings.
 ** @s1: A string.
 ** @s2: A string.
 ** @n: Amount of characters to compare.
 **
 ** Return: 1 if the strings don't match otherwise 0
 **/
int custom_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (s1 == NULL)
	return (-1);

	for (i = 0; i < n && s2[i]; i++)
{
	if (s1[i] != s2[i])
{
	return (1);
}
}

	return (0);
}

/**
 ** custom_strdup - Duplicate a string
 ** @str: String
 ** Return: Duplicate string, failed null
 **/
char *custom_strdup(char *str)
{
	size_t len, i;
	char *str2;

	len = custom_strlen(str);
	str2 = malloc(sizeof(char) * (len + 1));

	if (!str2)
{
	return (NULL);
}

	for (i = 0; i <= len; i++)
{
	str2[i] = str[i];
}

	return (str2);
}
