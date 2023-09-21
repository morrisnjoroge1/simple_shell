#include "shell.h"
char *_strdup(const char *str);
int _isdigit(char *s);

/**
 * _strdup - is a function that duplicates a string
 * @str: string to duplicate
 *
 * Return: string pointer of duplicated
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	/*mem allocation*/
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
	{
		return (NULL);
	}
	for (length++; length--; )
	{
		ret[length] = *--str;
	}
	return (ret);
}

/**
 * _isdigit - checks if string passed is a number
 * @s: string input
 *
 * Return: 1 if string is number 0 if not
 */

int _isdigit(char *s)
{
	int t;

	for (t = 0; s[t]; t++)
	{
		if (s[t] < 48 || s[t] > 57)
			return (0);
	}
	return (1);
}




