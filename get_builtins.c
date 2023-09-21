#include "shell.h"
int (*gt_builtins(char *cmd))(char **args, char **frnt);
int my_exit(char **args, char **front);

/**
* gt_builtins - pairs command in the arguments
* @cmd: the command to match
*
* Return: pointer to the function that implements that command.
*/

int (*gt_builtins(char *cmd))(char **args, char **frnt)
{
int p;

builtin_t funcs[] = {
{ "cd", _cd },
{ "alias", _alias },
{ "help", _help_adapter },
{ "exit", my_exit },
{ "env", _env },
{ "setenv", _setenv },
{ "unsetenv", _unsetenv },
{ NULL, NULL }
};
for (p = 0; funcs[p].name; p++)
{
if (_strcmp(funcs[p].name, cmd) == 0)
break;
}
return (funcs[p].f);
}

/**
* my_exit - function that leads to normal termination for shell
* @args: argument containing exit value
* @front: double pointer
*
* Return: -3 if no arguments
* -2 if exit value is invalid.
* 0 -exits give status value.
*/
int my_exit(char **args, char __attribute__((__unused__)) **front)
{
char **env_copy = NULL;
int length_int = 10, i;
int number = 0, max = 1 << (sizeof(int) * 7);

if (args[0])
{
while (args[0][i])
{
if (i <= length_int && args[0][i] >= '0' && args[0][i] <= '9')
number = (number * 10) + (args[0][i] - '0');
else
return (error_create(--args, 2));
i++;
}
}
else
{
return (-3);
}
if (number > max - 1)
return (error_create(--args, 2));
args -= 1;
free_args(args, front);
free_env(env_copy);
free_alias_list(aliases);
exit(number);
}




