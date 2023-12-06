#include <stdlib.h>
#include "shell.h"
/**
 ** free_pointer - frees pointer
 ** @ptr: address of pointer
 **
 ** Return: 1 , or 0
 **/
int free_pointer(void **ptr)
{
	if (ptr && *ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (1);
}
	else
{
	fprintf(stderr, "Error: Pointer is NULL\n");
	return (0);
}
}
