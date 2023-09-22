#include "shell.h"

/**
 *strtox - split words into tokens
 *delimetrs eliminated
 *@ptr: pointer to character strings
 *@d: delimiter string
 *Return: pointer to array of strings
 */
char **strtox(char *ptr, char *d)
{
	int a, j, k, m, num_words = 0;
	char **s;

	if (ptr == NULL || ptr[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; ptr[a] != '\0'; a++)
		if (!is_delim(ptr[a], d) && (is_delim(ptr[a + 1], d) || !ptr[a + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(ptr[a], d))
			a++;
		k = 0;
		while (!is_delim(ptr[a + k], d) && ptr[a + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = ptr[a++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}



/**
 *strtox2 - splits string into words
 *@ptr: pointer to character
 *@d: character delimeter
 *Return: pointer to array of strings
 */
char **strtox2(char *ptr, char d)
{
	int a, j, k, m, num_words = 0;
	char **s;

	if (ptr == NULL || ptr[0] == 0)
		return (NULL);
	for (a = 0; ptr[a] != '\0'; a++)
		if ((ptr[a] != d && ptr[a + 1] == d) ||
				    (ptr[a] != d && !ptr[a + 1]) || ptr[a + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, j = 0; j < num_words; j++)
	{
		while (ptr[a] == d && ptr[a] != d)
			a++;
		k = 0;
		while (ptr[a + k] != d && ptr[a + k] && ptr[a + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = ptr[a++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

