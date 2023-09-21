#include "shell.h"

/**
 * get_location - is a function to locate command
 * @command: The command to locate.
 *
 * Return: NULL - in case of error or no command
 */
char *get_location(char *command)
{
struct stat st;
char **path, *temp;
list_t *dirs, *head;

path = _getenv("PATH");
if (!path || !(*path))
{
return (NULL);
}
dirs = get_path_dir(*path + 5);
head = dirs;

for (dirs = head; dirs; dirs = dirs->next)
{
temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
if (!temp)
{
return (NULL);
}

_strcpy(temp, dirs->dir);
_strcat(temp, "/");
_strcat(temp, command);

if (stat(temp, &st) == 0)
{
free_list(head);
return (temp);
}
free(temp);
}
free_list(head);
return (NULL);
}



