#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @e: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *e)
{
	int i, j, k, m, num = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!e)
		e = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], e) && (is_delim(str[i + 1], e) || !str[i + 1]))
			num++;

	if (num == 0)
		return (NULL);
	s = malloc((1 + num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (is_delim(str[i], e))
			i++;
		k = 0;
		while (!is_delim(str[i + k], e) && str[i + k])
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
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @e: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char e)
{
	int i, j, k, m, num = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != e && str[i + 1] == e) ||
		    (str[i] != e && !str[i + 1]) || str[i + 1] == e)
			num++;
	if (num == 0)
		return (NULL);
	s = malloc((1 + num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (str[i] == e && str[i] != e)
			i++;
		k = 0;
		while (str[i + k] != e && str[i + k] && str[i + k] != e)
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
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

