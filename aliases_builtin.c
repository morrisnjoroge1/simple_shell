#include "shell.h"

void alias_print(alias_t *alias);
int _alias(char **args, char __attribute__((__unused__)) **front);
char **alias_replace(char **arg);
int set_alias(char *name, char *value);

/**
* _alias - function that finds a match in the builtin command
* @args: array of arguments
* @front: double pointer
*
* Return: -1 in case of error, 0 otherwise
*/
int _alias(char **args, char __attribute__((__unused__)) **front)
{
char *value;
int p;
int turn = 0;
alias_t *temp = aliases;

if (!args[0])
{
for (; temp; temp = temp->next)
{
alias_print(temp);
}
return (turn);
}

for (p = 0; args[p]; p++)
{
value = _strchr(args[p], '=');
if (!value)
{
temp = aliases;
while (temp && !_strcmp(args[p], temp->name))
{
temp = temp->next;
}
if (temp)
{
alias_print(temp);
}
else
{
turn = error_create(args + p, 1);
}
}
else
{
set_alias(args[p], value);
}
}

return (turn);
}

/**
* set_alias - function set existing alias 'name' with new value or create new
* @name: alias name
* @value: alias first value
* Return: 0 on success, 1 on error.
*/
int set_alias(char *name, char *value)
{
int length, i = 0, m = 0;
char *new_value = NULL;
alias_t *temp = aliases;

if (!new_value)
return (0);

*value = '\0';
value++;
length = _strlen(value) - _strspn(value, "'\"");
new_value = malloc(sizeof(char) * (length + 1));

while (value[i])
{
if (value[i] != '\'' && value[i] != '"')
{
while (value[i] != '\0' && value[i] != '\'' && value[i] != '"')
{
new_value[m++] = value[i++];
}
new_value[m] = '\0';
}
else
{
i++;
}
}

while (temp)
{
if (_strcmp(name, temp->name) == 0)
{
free(temp->value);
temp->value = new_value;
break;
}
temp = temp->next;
}

if (!temp)
{
add_alias_end(&aliases, name, new_value);
}

return (0);
}

/**
* alias_print - calculates the length of the string that needs to be printed
* @alias: pointer
* Return: void
*/
void alias_print(alias_t *alias)
{
int length = _strlen(alias->name) + _strlen(alias->value) + 5;
char *alias_string;
char *end_ptr;

alias_string = malloc(sizeof(char) * length);
if (!alias_string)
{
return;
}
end_ptr = alias_string;

end_ptr = _strcpy(end_ptr, alias->name);
end_ptr = _strcpy(end_ptr, "='");
end_ptr = _strcpy(end_ptr, alias->value);
end_ptr = _strcpy(end_ptr, "'\n");
length = end_ptr - alias_string;

write(STDOUT_FILENO, (const void *)alias_string, length);
free(alias_string);
}

/**
* alias_replace - takes an array of string as arg and replace
* with a matching alias
* @arg: pointer to argument
* Return: pointer.
*/
char **alias_replace(char **arg)
{
int found = 0;
int p = 0;
char *new_value;
alias_t *temp;

if (_strcmp(arg[0], "alias") == 0)
{
return (arg);
}

while (arg[p])
{
temp = aliases;
while (temp)
{
if (_strcmp(arg[p], temp->name) == 0)
{
new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
if (!new_value)
{
free_args(arg, arg);
return (NULL);
}
_strcpy(new_value, temp->value);
free(arg[p]);
arg[p] = new_value;
found = 1;
break;
}
temp = temp->next;
}

if (!found)
{
p++;
}
}

return (arg);
}


