#include "custom_shell.h"

/**
 ** custom_get_string_length - Returns the length of a string
 ** @str: The string whose length to check
 ** Return: Integer length of the string
 **/
int custom_get_string_length(char *str)
{
	int length = 0;

	if (!str)
{
	printf("Error: string is NULL\n");
	return (0);
}

	while (*str++)
{
	length++;
}

	return (length);
}

/**
 ** custom_compare_strings - Performs lexicographic comparison of two strings.
 ** @str1: The first string
 ** @str2: The second string
 ** Return: If str1 < str2, positive if str1 > str2, zero if str1 == str2
 **/
int custom_compare_strings(char *str1, char *str2)
{
	while (*str1 && *str2)
{
	if (*str1 != *str2)
	return (*str1 - *str2);
	str1++;
	str2++;
}

	if (*str1 == *str2)
	return (0);
	else
	return (*str1 < *str2 ? -1 : 1);
}

/**
 ** custom_string_starts_with - Checks if needle starts with haystack
 ** @haystack: String to search
 ** @needle: The substring to find
 ** Return: Address of the next char of haystack or NULL
 **/
char *custom_string_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	if (*needle++ != *haystack++)
	return (NULL);

	return ((char *)haystack);
}

/**
 ** custom_strcat - Concatenates two strings
 ** @dest: The destination buffer
 ** @src: The source buffer
 ** Return: Pointer to the destination buffer
 **/
char *custom_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
	dest++;

	while (*src)
	*dest++ = *src++;

	*dest = *src;

	return (ret);
}
