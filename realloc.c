#include "shell.h"
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void lineptr_assign(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t line_get(char **lineptr, size_t *n, FILE *stream);

/**
* _realloc - functio that Reallocates a memory block using malloc and free.
* @ptr: pointer to the memory .
* @old_size: size in bytes of the allocated space for ptr.
* @new_size: size in bytes for the new memory block.
*
* Return: new_size == old_size - ptr.
*         new_size == 0 and ptr is not NULL - NULL.
*         Otherwise - a pointer to the reallocated memory block.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *memry;
char *ptr_copy, *filler;
unsigned int i;

if (new_size == old_size)
return (ptr);

if (ptr == NULL)
{
memry = malloc(new_size);
if (memry == NULL)
return (NULL);

return (memry);
}

if (new_size == 0 && ptr != NULL)
{
free(ptr);
return (NULL);
}

ptr_copy = ptr;
memry = malloc(sizeof(*ptr_copy) * new_size);
if (memry == NULL)
{
free(ptr);
return (NULL);
}

filler = memry;

for (i = 0; i < old_size && i < new_size; i++)
filler[i] = *ptr_copy++;

free(ptr);
return (memry);
}

/**
* lineptr_assign - Reassigns the lineptr variable for _getline.
* @lineptr: buffer to  input string.
* @n: size of lineptr.
* @buffer: string to assign to lineptr.
* @b: size of buffer.
*/
void lineptr_assign(char **lineptr, size_t *n, char *buffer, size_t b)
{
if (*lineptr == NULL)
{
if (b > 120)
*n = b;
else
*n = 120;
*lineptr = buffer;
}
else if (*n < b)
{
if (b > 120)
*n = b;
else
*n = 120;
*lineptr = buffer;
}
else
{
_strcpy(*lineptr, buffer);
free(buffer);
}
}

/**
* line_get - Reads input from a stream.
* @lineptr: buffer to store  input.
* @n: size of lineptr.
* @stream: stream to read from.
*
* Return: number of bytes.
*/
ssize_t line_get(char **lineptr, size_t *n, FILE *stream)
{
static ssize_t i;
ssize_t ret;
char c = 'x', *buffer;
int z;

if (i == 0)
fflush(stream);
else
return (-1);
i = 0;

buffer = malloc(sizeof(char) * 120);
if (!buffer)
return (-1);

while (c != '\n')
{
z = read(STDIN_FILENO, &c, 1);
if (z == -1 || (z == 0 && i == 0))
{
free(buffer);
return (-1);
}
if (z == 0 && i != 0)
{
i++;
break;
}

if (i >= 120)
buffer = _realloc(buffer, i, i + 1);

buffer[i] = c;
i++;
}
buffer[i] = '\0';

lineptr_assign(lineptr, n, buffer, i);

ret = i;
if (z != 0)
i = 0;
return (ret);
}


