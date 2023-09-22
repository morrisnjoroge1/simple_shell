#include "shell.h"

/**
 *prints_error - prints the errors in shell
 *@infor: pointer to structure info_t
 *@pstr: pointer to character
 *Return: void
 */
void prints_error(info_t *infor, char *pstr)
{
	_eputs(infor->fname);
	_eputs(": ");
	print_d(infor->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infor->argv[0]);
	_eputs(": ");
	_eputs(estr);
}


/**
 *print_decimal - Prints decimal of base 10
 *@input: user input
 *@pd: file descriptor
 *Return: 0
 */
int print_decimal(int input, int pd)
{
	int (*__putchar)(char) = _putchar;
	int a, counter = 0;
	unsigned int _abs_, current;

	if (pd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + current / a);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	counter++;

	return (counter);
}


/**
 *convert_number - converts numbers to decimal
 *@num: number to be converted
 *@base: base nummber
 *@flags: flags
 *Return: converted numbers string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 *remove_comments - deletes comments and replace 1st argument with "#"
 *@buf: pointer character buff
 *Return: void
 */
void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
