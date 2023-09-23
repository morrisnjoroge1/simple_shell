#include "shell.h"

/**
 *_eputchar - Similar to _putchar
 *Function that prints char int the standard error type
 *@c: pointer to character
 *Return: 0 on success or -1 if errors encounted
 */
int _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}


/**
 *_eputs - function that prints out a string if any
 *@ptr: pointer to character string
 *Return: void
 */
void _eputs(char *ptr)
{
	int a = 0;

	if (!ptr)/*check if string is null*/
		return;
	while (ptr[a] != '\0')
	{
		_eputchar(ptr[a]);
		a++;
	}
}

/**
 *_putfd - Similar to _putchar func although
 *it prints character c in specified file descriptor
 *@c: character pointer
 *@pd: file descriptor
 *Return: 0 on success or -1 otherwise
 */
int _putfd(char c, int pd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(pd, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}


/**
 *_putsfd - Print out the inputted string
 *@ptr: character pointer
 *@pd: file descriptor
 *Return: characters printed
 */
int _putsfd(char *ptr, int pd)
{
	int x = 0;

	if (!ptr)
		return (0);
	while (*ptr)
	{
		x += _putfd(*ptr++, pd);
	}
	return (x);
}
