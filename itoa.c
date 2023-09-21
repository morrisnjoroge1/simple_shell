#include "shell.h"
/**
 * itoa - function converts an integer to a string
 * @num: input interger.
 *
 * Return: the string.
 */
char *itoa(int num)
{
	int length = num_len(num);
	int digit;
	int is_negative;
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
	{
		return (NULL);
	}
	buffer[length--] = '\0';
	is_negative  = (num < 0) ? 1 : 0;
	num = (is_negative) ? -num : num;

	while (num > 0)
	{
		digit = num % 10;
		buffer[length--] = digit + '0';
		num /= 10;
	}

	if (is_negative)
	{
		buffer[length] = '-';
	}
	return (buffer);
}




