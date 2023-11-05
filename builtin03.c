#include "custom_shell.h"

/**
 ** display_environment - Display Environment Variable
 ** @command: Parsed Command
 ** @status: Status of Last Command Executed
 ** Return: Always 0
 **/
int display_environment(__attribute__((unused)) char **command, __attribute__((unused)) int status)
{
	size_t i;
	int length;

	for (i = 0; my_environ[i] != NULL; i++)
{
	length = _strlen(my_environ[i]);
	write(STDOUT_FILENO, my_environ[i], length);
	write(STDOUT_FILENO, "\n", 1);
}
	return (0);
}

/**
 ** display_help_info - Display Help Information for Builtin
 ** @command: Parsed Command
 ** @status: Status Of Last Command Executed
 ** Return: 0 Success, -1 Fail
 **/
int display_help_info(char **command, __attribute__((unused)) int status)
{
	int fd, fw, rd = 1;
	char character;

	fd = open(command[1], O_RDONLY);
	if (fd < 0)
{
	perror("Error");
	return (0);
}
	while (rd > 0)
{
	rd = read(fd, &character, 1);
	fw = write(STDOUT_FILENO, &character, rd);
	if (fw < 0)
{
	return (-1);
}
}
	_putchar('\n');
	return (0);
}

/**
 ** execute_echo - Execute Echo Cases
 ** @status: Status Of Last Command Executed
 ** @command: Parsed Command
 ** Return: Always 0 Or Execute Normal Echo
 **/
int execute_echo(char **command, int status)
{
	char *path;
	unsigned int parent_pid = getppid();

	if (_strncmp(command[1], "$?", 2) == 0)
{
	print_number_in(status);
	PRINTER("\n");
}
	else if (_strncmp(command[1], "$$", 2) == 0)
{
	print_number(parent_pid);
	PRINTER("\n");
}
	else if (_strncmp(command[1], "$PATH", 5) == 0)
{
	path = _getenv("PATH");
	PRINTER(path);
	PRINTER("\n");
	free(path);
}
	else
	return (print_echo(command));

	return (1);
}

#include "custom_shell.h"

/**
 ** display_history - Display History Of User Input in Custom Shell
 ** @command: Parsed Command
 ** @status: Status Of Last Execute
 ** Return: 0 Success, -1 Fail
 **/
int display_history(__attribute__((unused)) char **command, __attribute__((unused)) int status)
{
	char *filename = ".custom_shell_history";
	FILE *file_pointer;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;
	char *error_message;

	file_pointer = fopen(filename, "r");
	if (file_pointer == NULL)
{
	return (-1);
}
	while ((getline(&line, &len, file_pointer)) != -1)
{
	counter++;
	error_message = _itoa(counter);
	PRINTER(error_message);
	free(error_message);
	PRINTER(" ");
	PRINTER(line);
}
	if (line)
	free(line);
	fclose(file_pointer);
	return (0);
}

/**
 ** execute_normal_echo - Execute Normal Echo
 ** @command: Parsed Command
 ** Return: 0 Success, -1 Fail
 **/
int execute_normal_echo(char **command)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
{
	if (execve("/bin/echo", command, my_environ) == -1)
{
	return (-1);
}
	exit(EXIT_FAILURE);
}
	else if (pid < 0)
{
	return (-1);
}
	else
{
	do {
	waitpid(pid, &status, WUNTRACED);
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
	return (1);
}
