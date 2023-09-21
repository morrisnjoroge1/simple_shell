#include "shell.h"

/**
* not_open - can't open error if does not exist or no proper position
* @file_path: the file path
*
* Return: 127
*/
int not_open(char *file_path)
{
int length;
char *error;
char *history_str;
int i = 0;

history_str = itoa(history);
if (!history_str)
{
return (127);
}
length = _strlen(name) + _strlen(history_str) + _strlen(file_path) + 16;
/*mem allocation*/
error = malloc(sizeof(char) * (length + 1));
if (!error)
{
free(history_str);
return (127);
}
while (length > i)
{
error[i] = ' ';
i++;
}
_strcpy(error, name);
_strcat(error, ":");
_strcat(error, history_str);
_strcat(error, ": Can't open ");
_strcat(error, file_path);
_strcat(error, "\n");

free(history_str);
write(STDERR_FILENO, error, length);
free(error);
return (127);
}





