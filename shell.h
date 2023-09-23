#ifndef SIMPLE_SHELL_HEADER
#define SIMPLE_SHELL_HEADER

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

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct listabc - singly linked list
 * @num: the number field
 * @ptr: a string
 * @next: points to the next node
 */
typedef struct listabc
{
	int num;
	char *ptr;
	struct listabc *next;
} list_t;

/**
 * struct passinfor - structure containing all the possible prototypes
 *used in the shell program
 * @arg: a string  character of  arguements
 * @argv:an array of string arguments from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @_line_count: the error count(s)
 * @err_num: the error code for exit()s
 * @line_count_flag: count the line of input
 * @fname: the  filename
 * @env: linked list local copy of environ
 * @environ: custom  copy of environ from Local env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_command: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfor
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int _line_count;
	int err_num;
	int line_count_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd*/
	int cmd_buf_command; /* CMD_command ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @command: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *command;
	int (*func)(info_t *);
} builtin_t;

/*ALL THE PROGRAM PROTOTYPES*/

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int is_cmd(info_t *, char *);
char *_dupchars(char *, int, int);
char *find_path(info_t *, char *, char *);

int loophsh(char **);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *start_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtox(char *, char *);
char **strtox2(char *, char);

char *_memset(char *, char, unsigned int);
void f_free(char **);
void *_realloc(void *, unsigned int, unsigned int);
int b_free(void **);

int x_interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erritoa(char *);

void prints_error(info_t *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);

int my_history(info_t *);
int my_alias(info_t *);

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigint_handler(int);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

char *_getenv(info_t *, const char *);
int my_env(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int populate_env_list(info_t *);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *get_history_file(info_t *info);
int hist_write(info_t *info);
int hist_read(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int hist_renumber(info_t *info);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_ptr(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t list_len(const list_t *);
char **list_to_string(list_t *);
size_t prints_list(const list_t *);
list_t *node_start_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int x_replace_alias(info_t *);
int y_replace_vars(info_t *);
int replace_string(char **, char *);

#endif
