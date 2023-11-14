#include "custom_shell.h"

/**
 ** custom_parse_cmd - Parse line of input
 ** @input: User input to parse
 ** Return: Array of char (parsed): Custom Shell
 **/
char **custom_parse_cmd(char *input)
{
	char **tokens;
	char *token;
	int i, buffsize = CUSTOM_BUFSIZE;

	if (input == NULL)
	return (NULL);

	tokens = malloc(sizeof(char *) * buffsize);
	if (!tokens)
{
	perror("hsh");
	return (NULL);
}

	token = custom_strtok(input, "\n ");
	for (i = 0; token; i++)
{
	tokens[i] = token;
	token = custom_strtok(NULL, "\n ");
}
	tokens[i] = NULL;

	return (tokens);
}
