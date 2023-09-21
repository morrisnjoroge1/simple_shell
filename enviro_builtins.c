#include "shell.h"
#include <string.h>

int _env(char **args, char __attribute__((__unused__)) **front);
int _setenv(char **args, char __attribute__((__unused__)) **front);
int _unsetenv(char **args, char __attribute__((__unused__)) **front);
char **_copyenv(void);
char **_getenv(char *var);

/**
* _env - function that prints the current enviroment
* @args: array of arguments
* @front: double pointer to args
* Return: -1 error, otherwise 0;
*/

int _env(char **args, char __attribute__((__unused__)) **front)
{
int index = 0;
char nc = '\n';

while (environ[index])
{
write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
write(STDOUT_FILENO, &nc, 1);
}
(void)args;
return (0);
}


/**
* _setenv - funtion that changes or adds an env variable to path
* @args: array of arguments passed to shell
* @front: double pointer to args
*
* Return: -1 for error, 0 for otherwise
*/
int _setenv(char **args, char __attribute__((__unused__)) **front)
{
char *new_val, **env_var = NULL, **new_env;
size_t env_size = 0;
int env_var_found = 0;
int new_env_index;
int env_index = 0;

if (!args[0] || !args[1])
{
return (error_create(args, -1));
}
new_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
if (!new_val)
{
return (error_create(args, -1));
}
_strcpy(new_val, args[0]);
_strcat(new_val, "=");
_strcat(new_val, args[1]);
while (environ[env_index])
{
if (_strcmp(args[0], environ[env_index]) == 0)
{
env_var = &environ[env_index];
env_var_found = 1;
break;
}
env_index++;
}
if (env_var_found)
{
free(env_var);
*env_var = new_val;
return (0);
}
while (environ[env_size])
{
env_size++;
}
new_env = malloc(sizeof(char *) * (env_size + 2));
if (!new_env)
{
free(new_val);
return (error_create(args, -1));
}
while (environ[new_env_index])
{
new_env[new_env_index] = environ[new_env_index];
new_env_index++;
}
new_env[new_env_index] = new_val;
new_env[new_env_index + 1] = NULL;
free(environ);
environ = new_env;
return (0);
}

/**
* _unsetenv - unsets environment variable with a given name
* @args: array of arguments
* @front: pointer to arguments
*
* Return: -1 on error, otherwise 0.
*/
int _unsetenv(char **args, char __attribute__((__unused__)) **front)
{
int env_index = 0, env_index2 = 0;
char **env_var, **new_env;
size_t size = 0;

if (!args[0])
return (error_create(args, -1));
env_var = _getenv(args[0]);
if (!env_var)
return (0);

for (size = 0; environ[size]; size++)
;

new_env = malloc(sizeof(char *) * size);
if (!new_env)
return (error_create(args, -1));

for (env_index = 0, env_index2 = 0; environ[env_index]; env_index++)
{
if (*env_var == environ[env_index])
{
free(*env_var);
continue;
}
new_env[env_index2] = environ[env_index];
env_index2++;
}
free(environ);
environ = new_env;
environ[size - 1] = NULL;

return (0);
}

/**
* _getenv - function that get value of env variable
*  @var:name of env variablev to get
*
*  Return: value, NULL if value does not exist.
*/
char **_getenv(char *var)
{
int index, len;

	len = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}



/**
* _copyenv - function that copies the environment variables to a new array
*
* Return: NULL incase of error or pointer.
*/
char **_copyenv(void)
{
size_t size = 0;
char **new_environ;
int index = 0;

for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}


