#include "shell.h"

int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/**
* _strchr - is a function that Locates a character in a string.
* @s: string to be searched.
* @c: character to be located.
*
* Return: If c is found - a pointer to the first occurence.
*         If c is not found - NULL.
*/
char *_strchr(char *s, char c)
{
int i;
for (i = 0; s[i]; i++)
{
if (s[i] == c)
return (s + i);
}
return (NULL);
}

/**
* _strcmp - function that Compares two strings lexicographically.
* @s1: The first string to be compared.
* @s2: The second string to be compared.
*
* Return: Positive byte difference if s1 > s2
*         0 if s1 = s2
*         Negative byte difference if s1 < s2
*/

int _strcmp(const char *s1, const char *s2)
{
int i;
for (i = 0; s1[i] && s2[i]; i++)
{
if (s1[i] != s2[i])
return (s1[i] - s2[i]);
}
return (0);
}

/**
* _strspn - function that Gets number of a prefix in substring.
* @s:  string to be searched.
* @accept: prefix to be counted.
*
* Return: number of bytes in s which
*         consist only of bytes from accept.
*/

int _strspn(char *s, char *accept)
{
int bytes = 0;
int i, j;

for (i = 0; s[i]; i++)
{
for (j = 0; accept[j]; j++)
{
if (s[i] == accept[j])
{
bytes++;
break;
}
}
}
return (bytes);
}

/**
* _strncmp - function that Compare two char in strings.
* @s1: Pointer to a string.
* @s2: Pointer to a string.
* @n: The first n bytes of the strings to compare.
*
* Return: negative if s1 is less than s2.
*         0 if s1 and s2 are equal.
*         positive if s1 is graeter than s2.
*         -15 if not equal.
*/

int _strncmp(const char *s1, const char *s2, size_t n)
{
size_t i;

for (i = 0; s1[i] && s2[i] && i < n; i++)
{
if (s1[i] > s2[i])
return (s1[i] - s2[i]);
else if (s1[i] < s2[i])
return (s1[i] - s2[i]);
}
if (i == n)
return (0);
else
return (-15);
}




