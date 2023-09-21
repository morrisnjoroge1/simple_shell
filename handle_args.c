#include "shell.h"
int arg_handle(int *exter_ret);
int arg_run(char **front, char **args, int *exter_ret);
int arg_call(char **args, char **f, int *exter_ret);
char *get_args(char *line, int *exe_ret);

char *get_args(char *line, int *exe_ret)
{
size_t n = 0;
ssize_t read;
char *prompt = "$ ";

if (line)
free(line);

read = line_get(&line, &n, STDIN_FILENO);
if (read == -1)
return (NULL);
if (read == 1)
{
history++;
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, prompt, 2);
return (get_args(line, exe_ret));
}

line[read - 1] = '\0';
replacement_variable(&line, exe_ret);
line_handler(&line, read);

return (line);
}


/**
* arg_handle - function that handles arguments in shell
* @exter_ret: pointer to integer
* Return: -2 END_OF_FILE, -1 cant be tokenized
*/
int arg_handle(int *exter_ret)
{
int i_inner = 0;
char **f, *l = NULL, **args;
int ret = 0, i_outer;

for (;;)
{
l = get_args(l, exter_ret);
if (!l)
{
return (END_OF_FILE);
}
args = _strtok(l, " ");
free(l);
if (!args)
{
return (ret);
}
if (args_check(args) != 0)
{
*exter_ret = 2;
free_args(args, args);
return (*exter_ret);
}
f = args;
i_outer = 0;
for (;;)
{
if (_strncmp(args[i_inner], ";", 1) == 0)
{
free(args[i_inner]);
args[i_inner] = NULL;
ret = arg_call(args, f, exter_ret);
args = &args[++i_inner];
i_inner = 0;
}
i_inner++;
if (!args[i_inner])
{
if (args)
{
ret = arg_call(args, f, exter_ret);
}
i_outer++;
break;
}
}
if (i_outer == 0)
{
free(f);
}
}
}

/**
* arg_run - is responsible for running the command specified by the user
* @front: pointer to string(cwd)
* @args: pointer to an array of strings
* @exter_ret: pointer to an integer(exit status)
*
* Return: last executed command
*/
int arg_run(char **front, char **args, int *exter_ret)
{
int index, ret;
int (*builtin)(char **args, char **front);

for (;;)
{
builtin = gt_builtins(args[0]);
if (builtin)
{
ret = builtin(args + 1, front);
if (ret != EXIT)
{
*exter_ret = ret;
}
}
else
{
*exter_ret = execute(args, front);
ret = *exter_ret;
}
history++;

for (index = 0; args[index]; index++)
{
free(args[index]);
}

if (!args[index])
{
break;
}
}

return (0);
}

/**
* arg_call -  executes the command specified by the user.
* @args: pointer to an array in command
* @f: string pointer
* @exter_ret: integer pointer for exit status
* Return: value
*/
int arg_call(char **args, char **f, int *exter_ret)
{
int i_index;
int i = 0, ret;

if (!args[0])
{
return (*exter_ret);
}
for (;;)
{
if (_strncmp(args[i], "||", 2) == 0)
{
free(args[i]);
args = alias_replace(args);
ret = arg_run(args, f, exter_ret);
if (*exter_ret != 0)
{
i = 0;
}
else
{
i_index = 0;
for (;;)
{
free(args[i_index]);
i_index++;
if (!args[i_index])
{
return (ret);
}
}
}
}
else if (_strncmp(args[i], "&&", 2) == 0)
{
free(args[i]);
args[i] = NULL;
args = alias_replace(args);
ret = arg_run(args, f, exter_ret);
if (exter_ret == 0)
i = 0;
}
else
{
i_index = 0;
for (;;)
{
free(args[i_index]);
i_index++;
if (!args[i_index])
{
return (ret);
}
}
}
i_index++;
if (!args[i])
{
args = alias_replace(args);
ret = arg_run(args, f, exter_ret);
}
}
return (ret);
}


