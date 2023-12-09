#include <shell.h>

/**
 ** _strncpy - string
 ** @dest: The destination
 ** @src: string
 ** @n: The amount of characters
 **
 ** Return: string
 **/
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	dest[i] = src[i];
	for ( ; i < n; i++)
	dest[i] = '\0';

	return (dest);
}

/**
 ** _strncat - Concatenates two strings
 ** @dest: The first string
 ** @src: The second string
 ** @n: The amount of bytes to be maximally used
 **
 ** Return: The concatenated string
 **/
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 ** _strchr - Locates a character
 ** @s: The new string
 ** @c: The character
 **
 ** Return: A pointer
 **/
char *_strchr(const char *s, int c)
{
	while (*s != (char)c)
{
	if (*s == '\0')
	return (NULL);
	s++;
}

	return ((char *)s);
}
