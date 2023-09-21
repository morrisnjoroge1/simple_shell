#include "shell.h"

int token_len(char *str, char *delim);
int token_count(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len -index marking the end
 * of the first token contained within a string.
 * @str: string to be searched.
 * @delim: delimiter character.
 *
 * Return: index marking the end of
 *         the intitial token pointed to be str.
 */
int token_len(char *str, char *delim)
{
	int i = 0, len = 0;

	while (*(str + i) && *(str + i) != *delim)
	{
		len++;
		i++;
	}

	return (len);
}

/**
 * token_count- number of delimited
 *                words contained within a string.
 * @str: string to be searched.
 * @delim: delimiter character.
 *
 * Return: number of words contained in str.
 */
int token_count(char *str, char *delim)
{
	int i, token = 0, len = 0;

	for (i = 0; *(str + i); i++)
		len++;

	for (i = 0; i < len; i++)
	{
		if (*(str + i) != *delim)
		{
			token++;
			i += token_len(str + i, delim);
		}
	}

	return (token);
}

/**
 * _strtok - Tokenizes a string.
 * @line: string.
 * @delim: delimiter character to tokenize the string by.
 *
 * Return: pointer to an array in string format
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int i = 0, tokens, t, letters, l;

	tokens = token_count(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[i] == *delim)
			i++;

		letters = token_len(line + i, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (i -= 1; i >= 0; i--)
				free(ptr[i]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[i];
			i++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}



