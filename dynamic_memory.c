#include <stdlib.h>
#include "custom_shell.h"

/**
 ** deallocate_pointer - Deallocates a pointer and sets the address to NULL
 ** @ptr: Address of the pointer to deallocate
 **
 ** Return: 1 if deallocated, otherwise 0.
 **/
int deallocate_pointer(void **ptr)
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
