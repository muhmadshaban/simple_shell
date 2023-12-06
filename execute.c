#include "shell.h"

/**
 ** handle_builtin - Handle Builtin
 ** @cmd: Parsed Command
 ** @er:statue of last Excute
 ** Return: -1 , or 0
 **/

int handle_builtin(char **cmd, int er)
{
	builtin bil[] = {
	{"cd", change_dir},
	{"env", dis_env},
	{"help", display_help},
	{"echo", echo_bul},
	{"history", history_dis},
	{NULL, NULL}
};
	int i = 0;

	while ((bil + i)->command)
{
	if (_strcmp(cmd[0], (bil + i)->command) == 0)
{
	return ((bil + i)->fun(cmd, er));
}
	i++;
}
	return (-1);
}
/**
 ** check_cmd - Excute Command
 **
 ** @cmd: Command
 ** @input: Input
 ** @c:Shell Excution Time
 ** @argv:Name of prog
 ** Return: 1 or 0 , or -1
 **/
int check_cmd(char **cmd, char *input, int c, char **argv)
{
	int status;
	pid_t pid;

	if (*cmd == NULL)
{
	return (-1);
}

	pid = fork();
	if (pid == -1)
{
	perror("Error");
	return (-1);
}

	if (pid == 0)
{
	if (_strncmp(*cmd, "./", 2) != 0 && _strncmp(*cmd, "/", 1) != 0)
{
	path_cmd(cmd);
}

	if (execve(*cmd, cmd, environ) == -1)
{
	print_error(cmd[0], c, argv);
	free(input);
	free(cmd);
	exit(EXIT_FAILURE);
}
	return (EXIT_SUCCESS);
}
	wait(&status);
	return (0);
}
/**
 ** signal_to_handel - Handle
 ** @sig:Captured Signal
 ** Return: Void
 **/
void signal_to_handel(int sig)
{
	if (sig == SIGINT)
{
	PRINTER("\n$ ");
}
}
/**
 ** signal_to_handle - Handle ^C
 ** @sig:Captured Signal
 ** Return: Void
 **/
void signal_to_handle(int sig)
{
	if (sig == SIGINT)
{
	PRINTER("\n$ ");
}
}
/**
 ** read_file - Read file
 ** @filename:File name
 ** @argv:Name of prog
 ** Return: -1 , or 0
 **/

void read_file(char *filename, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
{
	exit(EXIT_FAILURE);
}
	while ((getline(&line, &len, fp)) != -1)
{
	counter++;
	treat_file(line, counter, fp, argv);

}
	if (line)
	free(line);
	fclose(fp);
	exit(0);
}
/**
 ** treat_file - PARSE Check Command
 ** @line: Line
 ** @counter:Counter
 ** @fp:File Descriptor
 ** @argv:Name of prog
 ** Return : new line
 **/
void treat_file(char *line, int counter, FILE *fp, char **argv)
{
	char **cmd;
	int st = 0;

	cmd = parse_cmd(line);

	if (_strncmp(cmd[0], "exit", 4) == 0)
{
	exit_bul_for_file(cmd, line, fp);
}
	else if (check_builtin(cmd) == 0)
{
	st = handle_builtin(cmd, st);
	free(cmd);
}
	else
{
	st = check_cmd(cmd, line, counter, argv);
	free(cmd);
}
}
/**
 ** exit_bul_for_file - Exit Shell
 ** @line: Line
 ** @cmd: command
 ** @fd:File Descriptor
 ** Return : Case of file
 **/
void exit_bul_for_file(char **cmd, char *line, FILE *fd)
{
	int statue, i = 0;

	if (cmd[1] == NULL)
{
	free(line);
	free(cmd);
	fclose(fd);
	exit(errno);
}
	while (cmd[1][i])
{
	if (_isalpha(cmd[1][i++]) < 0)
{
	perror("illegal number");
}
}
	statue = _atoi(cmd[1]);
	free(line);
	free(cmd);
	fclose(fd);
	exit(statue);
}
