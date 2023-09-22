#include "shell.h"

/**
 *_strncat - Function that concantinates a string
 *@dest: destination or copy to
 *@src: source or copy from
 *@n: integer
 *Return: concanted string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 *_strncpy - Function that copies a string to specified location
 *@dest: destination or copy to
 *@src: source or copy from
 *@n: integer
 *Return: new string address
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}


/**
 *_strchr - Function that searches and locates a character in string
 *@s: pointer to character
 *@c: character to be located
 *Return: pointer to memory address of located character
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
