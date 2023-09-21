#include "shell.h"


/**
* free_env - frees the memory allocated  of the env variables.
* @env_copy: pointer to an array of pointers to strings
*
* Return: NULL or frees memory.
*/
void free_env(char **env_copy)
{
int i;

if (!env_copy)
{
return;
}
for (i = 0; env_copy[i]; i++)
{
free(env_copy[i]);
}
free(env_copy);
}



