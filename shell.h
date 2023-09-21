#ifndef _SHELL_H_
#define _SHELL_H_


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

/*end of file and exit - status of shell*/
#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int history;

/**
 * struct builtin_s - new struct type that handles aliases(shortcuts).
 * @name: name of the builtin command.
 * @f: function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;


/**
 * struct list_s - new struct type defining a linked list.
 * @dir: path to directory .
 * @next: pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;


/**
 * struct alias_s -  struct defining aliases.
 * @name: name of the alias.
 * @value: value of the alias.
 * @next: pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/*main*/
int execute(char **args, char **front);
int main(int argc, char *argv[]);
void proc_file_commands(char *filename);
char *get_location(char *command);
char *fill_path_dir(const char *path);
list_t *get_path_dir(const char *path);


/*builtins*/
int (*gt_builtins(char *cmd))(char **args, char **frnt);
int my_exit(char **args, char __attribute__((__unused__)) **front);
int _env(char **args, char **front);
int _setenv(char **args, char __attribute__((__unused__)) **front);
int _unsetenv(char **args, char __attribute__((__unused__)) **front);
char **_copyenv(void);
char **_getenv(char *var);
int _help(const char **args, char __attribute__((__unused__)) **front);
int _cd(char **args, char __attribute__((__unused__)) **front);
int _alias(char **args, char **front);

/*string*/
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
char *_strdup(const char *str);
int _isdigit(char *s);
int num_len(int num);

int args_check(char **args);
char *itoa(int num);
int token_len(char *str, char *delim);
int token_count(char *str, char *delim);
char **_strtok(char *line, char *delim);
void free_env(char **env_copy);
int arg_handle(int *exter_ret);
int arg_run(char **front, char **args, int *exter_ret);
int not_open(char *file_path);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void lineptr_assign(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t line_get(char **lineptr, size_t *n, FILE *stream);
int _cd(char **args, char __attribute__((__unused__)) **front);


/*helper*/
void line_handler(char **line, ssize_t read);
void ops_logic(char *line, ssize_t *new_len);
ssize_t new_length(char *line);
void x_help_env(void);
void x_help_setenv(void);
void x_help_unsetenv(void);
void x_help_history(void);
void x_help_all(void);
void x_help_alias(void);
void x_help_cd(void);
void x_help_exit(void);
void x_help_help(void);
void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void replacement_variable(char **args, int *exe_ret);

/*error*/
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);
int error_create(char **args, int err);

/*aliases_builtins*/
int _alias(char **args, char __attribute__((__unused__)) **front);
void alias_print(alias_t *alias);
char **alias_replace(char **arg);
/*env_builtins*/
int _env(char **args, char __attribute__((__unused__)) **front);
int _setenv(char **args, char **front);
int _unsetenv(char **args, char **front);
char **_copyenv(void);
char **_getenv(char *var);

/*node_list*/
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

/*helper*/
char *get_args(char *line, int *exe_ret);
void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);
int _help_adapter(char **args, char **front);

#endif /*shell_h*/


