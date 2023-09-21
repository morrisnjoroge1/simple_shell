#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
* _strlen - length of string
* @s: A pointer to the characters string.
*
* Return: The length of the character string.
*/

int _strlen(const char *s)
{
int length = 0;

if (!s)
return (0);
for (length = 0; s[length]; length++)
	;
return (length);
}

/**
* _strncat - function that concatenates two strings
* @n: number of bytes from source
* @dest: the destination buffer
* @src: the source buffer
*
* Return: pointer to destination buffer
*/

char *_strncat(char *dest, const char *src, size_t n)
{
size_t dest_len = _strlen(dest);
size_t i;

for (i = 0; i < n && src[i] != '\0'; i++)
dest[dest_len + i] = src[i];
dest[dest_len + i] = '\0';

return (dest);
}

/**
* _strcpy - Copies the string pointed to by src, including the
*           terminating null byte, to the buffer pointed by des.
* @dest: Pointer to the destination of copied string.
* @src: Pointer to the src of the source string.
*
* Return: Pointer to dest.
*/

char *_strcpy(char *dest, const char *src)
{
char *p = dest;

while (*src != '\0')
*p++ = *src++;
*p = '\0';

return (dest);
}


/**
* _strcat - function that Concantenates two strings.
* @dest: is a Pointer to destination string.
* @src: is a Pointer to source string.
*
* Return: Pointer to destination string.
*/

char *_strcat(char *dest, const char *src)
{
char *destTemp;
const char *srcTemp;

destTemp = dest;
srcTemp = src;

while (*destTemp != '\0')
destTemp++;

while (*srcTemp != '\0')
*destTemp++ = *srcTemp++;
*destTemp = '\0';
return (dest);
}




