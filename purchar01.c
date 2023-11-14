#include "custom_shell.h"

/**
 ** custom_putchar - Writes the character c to stdout
 ** @c: The character to print
 **
 ** Return: On success 1.
 ** On error, -1 is returned, and errno is set appropriately.
 **/
int custom_putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 ** custom_print_error - Display error based on command and
 ** how many times shell looped
 ** @input: User input
 ** @counter: Simple Shell count loop
 ** @argv: Program name
 **
 ** Return: Void
 **/
void custom_print_error(char *input, int counter, char **argv)
{
	char *er;

	CUSTOM_PRINTER(argv[0]);
	CUSTOM_PRINTER(": ");
	er = custom_itoa(counter);
	CUSTOM_PRINTER(er);
	free(er);
	CUSTOM_PRINTER(": ");
	CUSTOM_PRINTER(input);
	CUSTOM_PRINTER(": not found\n");
}
