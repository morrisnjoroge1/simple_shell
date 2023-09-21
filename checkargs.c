#include "shell.h"

/**
* args_check - it Checks if there are any leading ';', ';;', '&&', or '||'.
* @args: pointer
*
* Return: -2 for invalid position, 0 otherwise
*/
int args_check(char **args)
{
char *current, *next;
size_t i = 0, j;


while (args[i])
{
current = args[i];
}
if (current[0] == ';' || current[0] == '&' || current[0] == '|')
{
if (i == 0 || current[1] == ':')
{
return (error_create(&args[i], 2));
}
j = i + 1;
next = args[j];
while (next && (next[0] == ';' || next[0] == '&' || next[0] == '|'))
{
j++;
next = args[j];
}
if (next)
{
return (error_create(&args[j], 2));
}
}
i++;
return (0);
}





