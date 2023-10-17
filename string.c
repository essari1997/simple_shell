#include "shell.h"

/**
 * _strl - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strl(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strc - performs lexicogarphic comparison of two strangs.
 * @s: the first strang
 * @s1: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strc(char *s, char *s1)
{
	while (*s && *s1)
	{
		if (*s != *s1)
			return (*s - *s1);
		s++;
		s1++;
	}
	if (*s == *s1)
		return (0);
	else
		return (*s < *s1 ? -1 : 1);
}

/**
 * starts - checks if needle starts with haystack
 * @h: string to search
 * @n: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts(const char *h, const char *n)
{
	while (*n)
		if (*n++ != *h++)
			return (NULL);
	return ((char *)h);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
