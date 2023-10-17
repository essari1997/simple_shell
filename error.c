#include "shell.h"

/**
 *_eput - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eput(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputc(str[i]);
		i++;
	}
}

/**
 * _eputc - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputc(char c)
{
	static int i;
	static char buf[WRITE_S];

	if (c == FLUSH || i >= WRITE_S)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_S];

	if (c == FLUSH || i >= WRITE_S)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}

