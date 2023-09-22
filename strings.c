#include "shell.h"

/**
 *_strlen- checks for the length of string
 *@s: character pointer to string
 *Return: length of string
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}


/**
 *_strcmp - Function that concantates between strings
 *@s1: string one
 *@s2: string two
 *Return:  negative if s1 < s2, positive if s1 > s2, zero if s1 == s
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}


/**
 *start_with - checks if neddle starts with haystack
 *@haystack: string search
 *@needle: substring finding
 *Return: null or address of next string
 */
char *start_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}


/**
 *_strcat - concatenates two string
 *@dest: destinaton
 *@src: source
 *Return: destination pointeir
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
