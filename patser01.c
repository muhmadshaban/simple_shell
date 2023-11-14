#include "custom_shell.h"

/**
 ** custom_is_executable_command - Determines if a file is an executable command
 ** @info: The info struct
 ** @file_path: Path to the file
 **
 ** Return: 1 if true, 0 otherwise
 **/
int custom_is_executable_command(info_t *info, char *file_path)
{
	struct stat st;

	(void)info;
	if (!file_path || stat(file_path, &st))
{
	fprintf(stderr, "Error: Could not find file path.\n");
	return (0);
}
	if (st.st_mode & S_IFREG)
{
	return (1);
}
	return (0);
}

/**
 ** custom_duplicate_chars - Duplicates characters
 ** @path_str: The PATH string
 ** @start_index: Starting index
 ** @stop_index: Stopping index
 **
 ** Return: Pointer to the new buffer
 **/
char *custom_duplicate_chars(char *path_str, int start_index, int stop_index)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start_index; i < stop_index; i++)
{
	if (path_str[i] != ':')
{
	buffer[k++] = path_str[i];
}
}
	buffer[k] = 0;
	return (buffer);
}

/**
 ** custom_find_path - Finds the cmd in the PATH string
 ** @info: The info struct
 ** @path_str: The PATH string
 ** @cmd: The cmd to find
 **
 ** Return: Full path of cmd if found or NULL
 **/
char *custom_find_path(info_t *info, char *path_str, char *cmd)
{
	int i = 0, current_position = 0;
	char *path;

	if (!path_str)
{
	fprintf(stderr, "Error: No PATH string provided.\n");
	return (NULL);
}
	if ((custom_str_length(cmd) > 2) && custom_starts_with(cmd, "./"))
{
	if (custom_is_executable_command(info, cmd))
{
	return (cmd);
}
}
	while (1)
{
	if (!path_str[i] || path_str[i] == ':')
{
	path = custom_duplicate_chars(path_str, current_position, i);
	if (!*path)
{
	custom_strncat(path, cmd);
}
	else
{
	custom_strncat(path, "/");
	custom_strncat(path, cmd);
}
	if (custom_is_executable_command(info, path))
	return (path);
	if (!path_str[i])
	break;
	current_position = i;
}
	i++;
}
	return (NULL);
}
