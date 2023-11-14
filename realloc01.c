#include "custom_shell.h"
#include <stdlib.h>
#include <string.h>

/**
 ** custom_memset_fill - Fills memory with a constant byte
 ** @dest: Pointer to the memory area
 ** @fill_byte: The byte to fill *dest with
 ** @num_bytes: The number of bytes to be filled
 ** Return: (dest) A pointer to the memory area dest
 **/
char *custom_memset_fill(char *dest, char fill_byte, unsigned int num_bytes)
{
	unsigned int i;

	for (i = 0; i < num_bytes; i++)
	dest[i] = fill_byte;

	return (dest);
}

/**
 ** custom_free_str_arr - Frees a string of strings
 ** @str_arr: String of strings
 **/
void custom_free_str_arr(char **str_arr)
{
	char **arr_ptr = str_arr;

	if (!str_arr)
	return;

	while (*str_arr)
	free(*str_arr++);

	free(arr_ptr);
}

/**
 ** custom_realloc_mem - Reallocates a block of memory
 ** @ptr: Pointer to the previous malloc'ated block
 ** @old_size: Byte size of the previous block
 ** @new_size: Byte size of the new block
 ** Return: Pointer to the old block
 **/
void *custom_realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
	return (malloc(new_size));

	if (!new_size)
	return (free(ptr), NULL);

	if (new_size == old_size)
	return (ptr);

	p = malloc(new_size);

	if (!p)
	return (NULL);

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
	p[old_size] = ((char *)ptr)[old_size];

	free(ptr);

	return (p);
}
