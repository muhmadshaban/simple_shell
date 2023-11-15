#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 ** struct liststr - singly linked list
 ** @num: the number field
 ** @str: a string
 ** @next: points to the next node
 **/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 **struct passinfo - contains pseudo-arguements to pass into a function,
 **allowing uniform prototype for function pointer struct
 **@arg: a string generated from getline containing arguements
 **@argv: an array of strings generated from arg
 **@path: a string path for the current command
 **@argc: the argument count
 **@line_count: the error count
 **@err_num: the error code for exit()s
 **@linecount_flag: if on count this line of input
 **@fname: the program filename
 **@env: linked list local copy of environ
 **@environ: custom modified copy of environ from LL env
 **@history: the history node
 **@alias: the alias node
 **@env_changed: on if environ was changed
 **@status: the return status of the last exec'd command
 **@cmd_buf: address of pointer to cmd_buf, on if chaining
 **@cmd_buf_type: CMD_type ||, &&, ;
 **@readfd: the fd from which to read line input
 **@histcount: the history line number count
 **/
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 ** struct builtin - contains a builtin string and related function
 ** @type: the builtin command flag
 ** @func: the function
 **/
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

	int check_interactive(info_t *info)
	int is_separator(char c, char *separator)
	int is_alpha_char(int c)
	int str_to_int(char *s)
	int display_environment(__attribute__((unused)) char **command, __attribute__((unused)) int status)
	int display_help_info(char **command, __attribute__((unused)) int status)
	int execute_echo(char **command, int status)
	int display_history(__attribute__((unused)) char **command, __attribute__((unused)) int status)
	int execute_normal_echo(char **command)
	int display_command_history(info_t *info)
	int clear_alias(info_t *info, char *alias_string)
	int create_alias(info_t *info, char *alias_string)
	int print_alias_command(list_t *node)
	int display_aliases(info_t *info)
	void exit_shell(char **cmd, char *input, char **argv, int c)
	int change_directory(char **cmd, __attribute__((unused))int er)
	int deallocate_pointer(void **ptr)
	int print_custom_environment(info_t *info)
	char *get_custom_env_var(info_t *info, const char *name)
	int set_custom_env_var(info_t *info)
	int unset_custom_env_var(info_t *info)
	int populate_custom_env_list(info_t *info)
	void _custom_eputs(char *str)
	int _custom_eputchar(char c)
	int _custom_putfd(char c, int fd)
	int _custom_putsfd(char *str, int fd)
	int _custom_erratoi(char *s)
	void custom_print_error(info_t *info, char *estr)
	int custom_print_d(int input, int fd)
	char *custom_convert_number(long int num, int base, int flags)
	void custom_remove_comments(char *buf)
	int custom_handle_builtin(char **cmd, int er)
	int custom_check_cmd(char **cmd, char *input, int c, char **argv)
	void custom_signal_to_handle(int sig)
	void custom_signal_handler(int sig)
	void custom_read_file(char *filename, char **argv)
	void custom_treat_file(char *line, int counter, FILE *fp, char **argv)
	void custom_exit_built_in_for_file(char **cmd, char *line, FILE *fd)
	char *custom_strncpy(char *dest, const char *src, size_t n)
	char *custom_strncat(char *dest, const char *src, size_t n)
	char *custom_strchr(const char *s, int c)
	int custom_path_command(char **cmd)
	char *custom_build(char *token, char *value)
	char *custom_getenv(char *name)
	char **custom_get_environment(info_t *info)
	int custom_unset_environment(info_t *info, char *env_var)
	int custom_set_environment_variable(info_t *info, char *variable, char *value)
	void custom_initialize_info(custom_info_t *info)
	void custom_set_info(custom_info_t *info, char **av)
	void custom_free_info(custom_info_t *info, int all)
	void custom_initialize_info(custom_info_t *info)
	void custom_set_info(custom_info_t *info, char **av)
	void custom_free_info(custom_info_t *info, int all)
	ssize_t custom_input_buffer(custom_info_t *info, char **buffer, size_t *buffer_length)
	ssize_t custom_get_input(custom_info_t *info)
	ssize_t custom_read_buffer(custom_info_t *info, char *buffer, size_t *buffer_size)
	int custom_get_line(custom_info_t *info, char **buffer_ptr, size_t *buffer_length)
	void custom_sigintHandler(__attribute__((unused))int sig_num)
	char *custom_get_history_file(custom_info_t *info)
	int custom_write_history(custom_info_t *info)
	int custom_read_history(custom_info_t *info)
	int custom_build_history_list(custom_info_t *info, char *buf, int line_count)
	int custom_renumber_history(custom_info_t *info)
	list_t *custom_add_node(list_t **head, const char *str, int num)
	list_t *custom_add_node_end(list_t **head, const char *str, int num)
	size_t custom_print_list_str(const list_t *head)
	int custom_delete_node_at_index(list_t **head, unsigned int index)
	void custom_free_list(list_t **head_pointer)
	size_t custom_get_list_length(const list_t *head)
	char **custom_list_to_strings(list_t *head)
	size_t custom_print_list(const list_t *head)
	list_t *custom_node_starts_with(list_t *node, char *prefix, char c)
	ssize_t custom_get_node_index(list_t *head, list_t *node)
	void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
	void custom_free_all(char **cmd, char *line)
	char *custom_memcpy(char *dest, char *src, unsigned int n)
	void *custom_fill_array(void *a, int el, unsigned int len)
	void *custom_calloc(unsigned int size)
	int custom_check_builtin(char **cmd)
	void custom_create_environment(char **envi)
	int custom_is_executable_command(info_t *info, char *file_path)
	char *custom_duplicate_chars(char *path_str, int start_index, int stop_index)
	char *custom_find_path(info_t *info, char *path_str, char *cmd)
	int custom_putchar(char c)
	void custom_print_error(char *input, int counter, char **argv)
	char **custom_parse_cmd(char *input)
	char *custom_memset_fill(char *dest, char fill_byte, unsigned int num_bytes)
	void *custom_realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size)
	int custom_shell(info_t *info, char **av)
	int custom_find_builtin(info_t *info)
	void custom_find_cmd(info_t *info)
	void custom_fork_cmd(info_t *info)
	char *custom_strcpy(char *dest, char *src)
	char *custom_strdup(const char *str)
	void custom_puts(char *str)
	int custom_putchar(char c)
	int custom_get_string_length(char *str)
	int custom_compare_strings(char *str1, char *str2)
	char *custom_string_starts_with(const char *haystack, const char *needle)
	char *custom_strcat(char *dest, char *src)
	char *custom_strcpy(char *dest, char *src)
	char *custom_strcat(char *dest, char *src)
	char *custom_strchr(char *s, char c)
	int custom_strncmp(const char *s1, const char *s2, size_t n)
	char *custom_strdup(char *str)
	int custom_isalpha(int c)
	char *custom_itoa(unsigned int n)
	void custom_array_rev(char *arr, int len)
	int custom_intlen(int num)
	void custom_prerror(char **argv, int c, char **cmd)
	char **custom_strtow(char *input_str, char *del_s)
	char **custom_strtow2(char *input_str, char del)
	int custom_is_chain_del(info_t *info, char *buf, size_t *cur_pos)
	void custom_chain_status(info_t *info, char *buf, size_t *cur_pos, size_t ist_pos, size_t buf_len)
	int custom_replace_alias(info_t *info)
	int custom_replace_vars(info_t *info)
	int custom_replace_string(char **old, char *new)


#endif
