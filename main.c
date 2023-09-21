#include "shell.h"

/*Function declarations*/
int execute(char **args, char **front);
int main(int argc, char *argv[]);
void proc_file_commands(char *filename);
void sig_handler(int sig);

/**
* sig_handler - function that print new prompt on a signal
* @sig: expected signal
*
*/
void sig_handler(int sig)
{
char *new_prompt = "\n$";

(void)sig;
signal(SIGINT, sig_handler);
write(STDIN_FILENO, new_prompt, 3);
}

/**
* proc_file_commands - checks for errors
* @filename: pointer file
*
* Return: (void)
*/
void proc_file_commands(char *filename)
{
FILE *fp;
char *line = NULL;
size_t line_size = 0;

/*Open the file*/
fp = fopen(filename, "r");
if (fp == NULL)
{
perror("Error opening file");
return;
}
/*Read the commands from the file*/
while (getline(&line, &line_size, fp) != -1)
{

int exter_ret = 0;/*integer value*/
int result = sscanf(line, "%d", &exter_ret);

if (result != 1)
{
fprintf(stderr, "Error converting line to integer: %s", line);
continue; /* Skip this line and move to the next one*/
}
/*execute command*/
arg_handle(&exter_ret);
/* Check exter_ret for any errors */
if (exter_ret != 0)
{
fprintf(stderr, "arg_handle returned an error: %d\n", exter_ret);
}
}
free(fp);
fclose(fp);
}

/**
* execute - it executes a command in a child process.
* @args: array of arguments.
* @front:  pointer to the beginning of args.
*
* Return: when error occurs - a corresponding error code.
*         O/w - exit value of the last executed command.
*/

int execute(char **args, char **front)
{
pid_t child_pid;
int status;
char *command = args[0];
int f = 0, ret = 0;
char **env_copy = NULL;

/*check if command is in path*/
if (command[0] != '/' && command[0] != '.')
{
command = get_location(command);
f = 1;
}
if (!command || (access(command, F_OK) == -1))
{
if (errno == EACCES)
ret = (errno == 0 ? 126 : 127);
}
/*fork child process*/
child_pid = fork();
if (child_pid == -1)
{
if (f)
free(command);
perror("Error forking child process");
return (1);
}
/*child process execute the command*/
if (child_pid == 0)
{

execve(args[0], args, environ);
if (errno == EACCES)
ret = atoi(error_126(args));
free_env(env_copy);
free_args(args, front);
free_alias_list(aliases);

perror("Error executing command");
_exit(ret);
}
else
{
/*wait - parent process, for the chold process to exit*/
wait(&status);

/*return exit status of child process*/
return (WEXITSTATUS(status));
}
if (f)
free(command);
return (ret);
}



/**
* main - simple unix command line interpreter.
* @argc: number of arguments supplied to the program.
* @argv: array of pointers to the arguments.
* Return: value of last command.
*/
int main(int argc, char *argv[])
{
int rtn;
int *out = &rtn;
int ret = 0;
char *prompt = "$", *new_line = "\n";
char **env_copy = NULL;

aliases = NULL;
name = argv[0];
history = 1;
signal(SIGINT, sig_handler);

*out = 0;
environ = _copyenv();
if (!environ)
{
exit(-100);
}
if (argc != 1)
{
proc_file_commands(argv[1]);
free_env(env_copy);
free_alias_list(aliases);
return (*out);
}
if (!isatty(STDIN_FILENO))
{
while (ret != END_OF_FILE && ret != EXIT)
ret = arg_handle(out);
free_env(env_copy);
free_alias_list(aliases);
return (*out);
}
while (1)
{
write(STDOUT_FILENO, prompt, 2);
ret = arg_handle(out);
if (ret == END_OF_FILE || ret == EXIT)
{
if (ret == END_OF_FILE)
write(STDOUT_FILENO, new_line, 1);
free_env(env_copy);
free_alias_list(aliases);
exit(*out);
}
}
free_env(env_copy);
free_alias_list(aliases);
return (*out);
}



