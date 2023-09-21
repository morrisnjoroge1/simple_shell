#include "shell.h"
#include <string.h>

char *fill_path_dir(const char *path);
list_t *get_path_dir(const char *path);

/**
* fill_path_dir - checks if ":" is in the working directory
* @path: pointer to char
*
* Return: path
*/
char *fill_path_dir(const char *path)
{
char *path_copy, *pwd;
int i, length = 0;

pwd = getenv("PWD");
i = 0;

while (path[i])
{
if (path[i] == ':')
{
if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
{
length += strlen(pwd) + 1;
}
else
{
length++;
}
}
else
{
length++;
}
i++;
}
path_copy = malloc(sizeof(char) * (length + 1));
if (!path_copy)
{
return (NULL);
}
path_copy[0] = '\0';
i = 0;

while (path[i])
{
if (path[i] == ':')
{
if (i == 0)
{
strcat(path_copy, pwd);
strcat(path_copy, (char *) ":");
}
else if (path[i + 1] == ':' || path[i + 1] == '\0')
{
strcat(path_copy, (char *) ':');
strcat(path_copy, pwd);
}
else
{
strcat(path_copy, (char *) ':');
}
}
else
{
strncat(path_copy, &path[i], 1);
}
i++;
}
return (path_copy);
}



/**
* get_path_dir - function that takes path to tokenize ':' in list
* @path: directory separated by ':'
*
* Return: list pointer
*/
list_t *get_path_dir(const char *path)
{
int i;
char **dir, *path_copy;
list_t *head = NULL;

path_copy = fill_path_dir(path);
if (!path_copy)
{
return (NULL);
}
dir = (char **) strtok(path_copy, (char *) ":");
free(path_copy);
if (!dir)
{
return (NULL);
}

i = 0;
while (dir[i])
{
if (add_node_end(&head, dir[i]) == NULL)
{
free_list(head);
free(head);
free(dir);
return (NULL);
}
i++;
}
free(dir);
return (head);
}



