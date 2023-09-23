#include "shell.h"

/**
 *_atoi - F unction that Convert a string int integer
 *@s: pointer to character string
 *Return: 0 if success
 */
int _atoi(char *s)
{
	int a, sign = 1, flag = 0, outputt;
	unsigned int results = 0;

	for (a = 0; s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			results *= 10;
			results += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		outputt = -results;
	else
		outputt = results;

	return (outputt);
}

/**
 *_erritoa - Creating a function that converts string into integer
 *@s: character pinter to string
 *Return: 0 if success or -1 otherwise
 */
int _erritoa(char *s)
{
	int a = 0;
	unsigned long int results = 0;

	if (*s == '+')
		s++;
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			results *= 10;
			results += (s[a] - '0');
			if (results > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (results);
}
