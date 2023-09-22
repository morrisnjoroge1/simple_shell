#include "shell.h"

/**
 *_strcpy - copies string
 *@dest: destination
 *@src: source
 *Return: address of new string copied
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}


/**
 *_strdup - duplicates string
 *@str: pointer to characacter string
 *Return: pointer to duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *rec;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	rec = malloc(sizeof(char) * (length + 1));
	if (!rec)
		return (NULL);
	for (length++; length--;)
		rec[length] = *--str;
	return (rec);
}


/**
 *replace_string - replaces a string
 *@oldest: old string
 *@newest: new string
 *Return: address of new string
 */
int replace_string(char **oldest, char *newest)
{
	free(*oldest);
	*oldest = newest;
	return (1);
}

