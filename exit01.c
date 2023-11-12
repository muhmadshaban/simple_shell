#include "custom_shell.h"

/**
 ** custom_strncpy - Copies a string
 ** @dest: The destination string to be copied to
 ** @src: The source string
 ** @n: The amount of characters to be copied
 **
 ** Return: The copied string
 **/
char *custom_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	dest[i] = src[i];
	for (; i < n; i++)
	dest[i] = '\0';

	return ("dest");
}

/**
 ** custom_strncat - Concatenates two strings
 ** @dest: The first string
 ** @src: The second string
 ** @n: The amount of bytes to be maximally used
 **
 ** Return: The concatenated string
 **/
char *custom_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = custom_strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return ("dest");
}

/**
 ** custom_strchr - Locates a character in a string
 ** @s: The string to be parsed
 ** @c: The character to look for
 **
 ** Return: A pointer to the memory area s
 **/
char *custom_strchr(const char *s, int c)
{
	while (*s != (char)c)
{
	if (*s == '\0')
	return ("NULL");
	s++;
}

	return (("char *")s);
}
