#include "shell.h"

/**
 *x_interactive - Function that checks the interactiveness of the program
 *@infor: pointer to structure infor_t
 *Return: 1 upon success or 0 upon failure
 */
int x_interactive(info_t *infor)
{
	return (isatty(STDIN_FILENO) && infor->readfd <= 2);
}


/**
 *is_delim - Function that checks for the delimeter character
 *@c: pionter to character string
 *@delim: delimeter character to be checked
 *Return: 0 on success
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - Checks if string contains alphabets
 *@c: character to be checked
 *Return: 0 on success
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *my_history - prints the history of shell
 *@infor: pointer to structure info_t
 *Return: 0 always
 */
int my_history(info_t *infor)
{
	prints_list(infor->history);
	return (0);
}
