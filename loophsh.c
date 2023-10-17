#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int b = 0;

	while (r != -1 && b != -2)
	{
		clear_i(info);
		if (inte(info))
			_puts("$ ");
		_eputc(FLUSH);
		r = get_i(info);
		if (r != -1)
		{
			set_i(info, av);
			b = find_b(info);
			if (b == -1)
				find_c(info);
		}
		else if (inte(info))
			_putchar('\n');
		free_i(info, 0);
	}
	write_h(info);
	free_i(info, 1);
	if (!inte(info) && info->status)
		exit(info->status);
	if (b == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (b);
}

/**
 * find_b - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_b(info_t *info)
{
	int i, built = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myh},
		{"history", _myhi},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strc(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built = builtintbl[i].func(info);
			break;
		}
	return (built);
}

/**
 * find_c - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_c(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_p(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_c(info);
	}
	else
	{
		if ((inte(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_c(info, info->argv[0]))
			fork_c(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_e(info, "not found\n");
		}
	}
}

/**
 * fork_c - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_c(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_i(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_e(info, "Permission denied\n");
		}
	}
}
