#include <shell.h>
/**
 ** free_info - Frees struct
 ** @info: Struct address
 ** @all: True if freeing all fields
 **/
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
{
	if (!info->cmd_buf)
	free(info->arg);
	if (info->env)
	free_list(&(info->env));
	if (info->history)
	free_list(&(info->history));
	if (info->alias)
	free_list(&(info->alias));
	ffree(info->environ);
	info->environ = NULL;
	bfree((void **)info->cmd_buf);
	if (info->readfd > 2)
	close(info->readfd);
	_putchar(BUF_FLUSH);
}
}
