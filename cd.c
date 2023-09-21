#include "shell.h"

int _cd(char **args, char __attribute__((__unused__)) **front);
int _help(const char **args, char __attribute__((__unused__)) **front);
int _help_adapter(char **args, char **front);

/**
* _cd - function that changes the current working directory
* @args: argument array
* @front: pointer to beginning of args
*
* Return: -2 if string is not a directory, -1 on error,
*/



int _cd(char **args, char __attribute__((__unused__)) **front)
{
char *old_pwd = NULL, *pwd = NULL;
char **directory_infor, *new_line = "\n";
struct stat dir;

old_pwd = getcwd(old_pwd, 0);
if (!old_pwd)
return (-1);

for (; *args; args++)
{
if ((*args)[0] == '-' || _strcmp(*args, "--") == 0)
{
if ((*args)[1] == '-' && ((*args)[2] == '\0' || (*args)[1] == '\0'))
{
if (_getenv("OLD_PWD") != NULL)
chdir(*_getenv("OLD_PWD") + 7);
}
else
{
free(old_pwd);
return (error_create(args, 2));
}
}
else
{
if (stat(*args, &dir) == 0 && S_ISDIR(dir.st_mode)
&& (dir.st_mode & S_IXUSR) != 0)
chdir(*args);
else
{
free(old_pwd);
return (error_create(args, 2));
}
}
}

pwd = getcwd(pwd, 0);
if (!pwd)
{
free(old_pwd);
return (-1);
}

directory_infor = (char **)malloc(sizeof(char *) * 2);
if (!directory_infor)
{
free(old_pwd);
free(pwd);
return (-1);
}

directory_infor[0] = "OLD_PWD";
directory_infor[1] = old_pwd;
if (_setenv(directory_infor, NULL) == -1)
{
free(old_pwd);
free(pwd);
free(directory_infor);
return (-1);
}

directory_infor[0] = "PWD";
directory_infor[1] = pwd;
if (_setenv(directory_infor, NULL) == -1)
{
free(old_pwd);
free(pwd);
free(directory_infor);
return (-1);
}

if (args[0] && args[0][0] == '-' && args[0][1] != '-')
{
write(STDOUT_FILENO, pwd, _strlen(pwd));
write(STDOUT_FILENO, new_line, 1);
}

free(old_pwd);
free(pwd);
free(directory_infor);

return (0);
}


/**
* _help - function that displays infor about builtin commands
* @args: array of arguments
* @front: args pointer(beginning)
*
* Return: -1 for error, 0 otherwise.
*/

int _help(const char **args, char __attribute__((__unused__)) **front)
{
int found = 0, i;

if (!args[0])
{
x_help_all();
}
else
{
const char *command[] = {
"alias", "cd", "env",
"setenv", "unsetenv", "help"
};
void (*help_functions[])(void) = {
x_help_alias, x_help_cd, x_help_env,
x_help_setenv, x_help_unsetenv, x_help_help
};
const int num_commands = sizeof(command) / sizeof(command[0]);

for (i = 0; i < num_commands; i++)
{
if (_strcmp(args[0], command[i]) == 0)
{
help_functions[i]();
found = 1;
break;
}
}

if (!found)
{
write(STDERR_FILENO, "Command not found\n", _strlen("Command not found\n"));
}
}

return (0);
}

/**
* _help_adapter - function that converts parameter types
* @args: array of arguments.
* @front: pointer arguments
* Return: help
**/

int _help_adapter(char **args, char **front)
{
const char **const_args = (const char **)args;
return (_help(const_args, front));
}


