#include "shell.h"

/**
 *_realloc - reallocates memory in heap
 *@ptr: pointer to character string
 *@old_size: old size
 *@new_size: new size memory
 *Return: void
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}


/**
 *_memset - Function that fills in memory with bytes
 *@s: character string pointer
 *@b: character
 *@n: integer
 *Return: pointer to memory area or location
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}


/**
 *f_free - frees memory allocated in heap
 *@ppd: pointer to character string
 *Return: void
 */
void f_free(char **ppd)
{
	char **a = ppd;

	if (!ppd)
		return;
	while (*ppd)
		free(*ppd++);
	free(a);
}


/**
 *b_free - frees lists
 *@ptr: double pointer to character string
 *Return: 1 if success or 0
 */
int b_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
