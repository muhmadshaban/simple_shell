#include "custom_shell.h"

/**
 ** custom_shell - Main shell loop
 ** @info: Parameter and return info struct
 ** @av: Argument vector from main()
 **
 ** Return: 0 on success, 1 on error, or error code
 **/
int custom_shell(info_t *info, char **av)
{
	ssize_t read_status = 0;
	int builtin_ret = 0;

	while (read_status != -1 && builtin_ret != -2)
{
	clear_info(info);
	if (custom_interactive(info))
	custom_puts("$ ");
	custom_eputchar(BUF_FLUSH);
	read_status = custom_get_input(info);
	if (read_status != -1)
{
	set_info(info, av);
	builtin_ret = custom_find_builtin(info);
	if (builtin_ret == -1)
	custom_find_cmd(info);
}
	else if (custom_interactive(info))
	custom_putchar('\n');
	free_info(info, 0);
}
	custom_write_history(info);
	free_info(info, 1);
	if (!custom_interactive(info) && info->status)
	exit(info->status);
	if (builtin_ret == -2)
{
	if (info->err_num == -1)
	exit(info->status);
	exit(info->err_num);
}
	return (builtin_ret);
}

/**
 ** custom_find_builtin - Finds a builtin command
 ** @info: Parameter and return info struct
 ** Return: -1 if builtin not found,
 ** 0 if builtin executed successfully,
 ** 1 if builtin found but not successful,
 ** -2 if builtin signals exit()
 **/
int custom_find_builtin(info_t *info)
{
	int i, builtin_ret = -1;
	custom_builtin_table builtintbl[] = {
	{"exit", custom_exit_shell},
	{"env", custom_print_environment},
	{"help", custom_print_help},
	{"history", custom_print_history},
	{"setenv", custom_set_env_var},
	{"unsetenv", custom_unset_env_var},
	{"cd", custom_change_dir},
	{"alias", custom_print_aliases},
	{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
	if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
{
	info->line_count++;
	builtin_ret = builtintbl[i].func(info);
	break;
}

	return (builtin_ret);
}

/**
 ** custom_find_cmd - Finds a command in PATH
 ** @info: Parameter and return info struct
 **
 ** Return: void
 **/
void custom_find_cmd(info_t *info)
{
	char *path = NULL;
	int i, num_args = 0;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
{
	info->line_count++;
	info->linecount_flag = 0;
}

	for (i = 0; info->arg[i]; i++)
	if (!custom_is_delimiter(info->arg[i], " \t\n"))
	num_args++;

	if (!num_args)
	return;

	path = custom_find_path(info, custom_get_env_var(info, "PATH="), info->argv[0]);

	if (path)
{
	info->path = path;
	custom_fork_cmd(info);
}
	else
{
	if ((custom_is_interactive(info) || custom_get_env_var(info, "PATH=") || info->argv[0][0] == '/') && custom_find_cmd(info, info->argv[0]))
	custom_fork_cmd(info);
	else if (*(info->arg) != '\n')
{
	info->status = 150;
	custom_print_error(info, "No Command\n");
}
}
}

/**
 ** custom_fork_cmd - Forks an exec thread to run cmd
 ** @info: Parameter and return info struct
 **
 ** Return: void
 **/
void custom_fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid == -1)
{

	perror("Fatal Error:");
	return;
}

	if (child_pid == 0)
{
	if (execve(info->path, info->argv, custom_get_environment(info)) == -1)
{
	free_info(info, 1);
	if (errno == EACCES)
	exit(98);
	exit(1);

}
}
	else
{
	wait(&(info->status));

	if (WIFEXITED(info->status))
{
	info->status = WEXITSTATUS(info->status);

	if (info->status == 150)
	custom_print_error(info, "Permission denied\n");
}
}
}
