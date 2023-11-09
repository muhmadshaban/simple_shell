nclude "custom_shell.h"

/**
 ** custom_signal_handler - Handle SIGINT (Ctrl+C)
 ** @sig: Captured Signal
 ** Return: Void
 **/
void custom_signal_handler(int sig)
{
	if (sig == SIGINT)
{
	custom_printer("\n$ ");
}
}

/**
 ** custom_read_file - Read Commands From a File
 ** @filename: Filename
 ** @argv: Program Name
 ** Return: -1 or 0
 **/
void custom_read_file(char *filename, char **argv)
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
	while (getline(&line, &len, fp) != -1)
{
	counter++;
	custom_treat_file(line, counter, fp, argv);
}
	if (line)
	free(line);
	fclose(fp);
	exit(0);
}

/**
 ** custom_treat_file - Parse, Check Command, Fork, Wait, and Execute in Lines of a File
 ** @line: Line From a File
 ** @counter: Error Counter
 ** @fp: File Descriptor
 ** @argv: Program Name
 ** Return: Execute a line, void
 **/
void custom_treat_file(char *line, int counter, FILE *fp, char **argv)
{
	char **cmd;
	int st = 0;

	cmd = custom_parse_cmd(line);

	if (_custom_strncmp(cmd[0], "exit", 4) == 0)
{
	custom_exit_built_in_for_file(cmd, line, fp);
}
	else if (custom_check_builtin(cmd) == 0)
{
	st = custom_handle_builtin(cmd, st);
	free(cmd);
}
	else
{
	st = custom_check_command(cmd, line, counter, argv);
	free(cmd);
}
}

/**
 ** custom_exit_built_in_for_file - Exit Shell in Case of File
 ** @cmd: Parsed Command
 ** @line: Line From a File
 ** @fd: File Descriptor
 ** Return: Case of Exit in a File Line
 **/
void custom_exit_built_in_for_file(char **cmd, char *line, FILE *fd)
{
	int status, i = 0;

	if (cmd[1] == NULL)
{
	free(line);
	free(cmd);
	fclose(fd);
	exit(errno);
}
	while (cmd[1][i])
{
	if (_custom_isalpha(cmd[1][i++]) < 0)
{
	perror("illegal number");
}
}
	status = _custom_atoi(cmd[1]);
	free(line);
	free(cmd);
	fclose(fd);
	exit(status);
}
