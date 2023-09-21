#include "shell.h"

/**
 * num_len - function counting digit lenght of a number
 * @num: number to measure
 *
 * Return: length of digit
 */
int num_len(int num)
{
	int length = 0;

	if (num == 0)
	{
		return (1); /*single digit zero*/
	}
	if (num < 0)
	{
		length++; /*account for negative sign*/
		num = -num; /*convert negative number to positive*/
	}
	while (num > 0)
	{
		length++;
		num /= 10; /*remove the last digit*/
	}
	return (length);
}




