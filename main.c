#include "shell.h"

/**
 * main - the main function
 * @argc: the argument count plus the ame of file
 * @argv: arrays of arguments and name of file
 * Return: 0 on succes
 */

int main(int argc, char **argv)
{
	char *buf = NULL;
	size_t n = 0;
	char *fnm = argv[0];

	(void)argc;

	signal(SIGINT, handle_sigint);
	while (ON)
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);
		if (_getline(&buf, &n, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		buf[_strcspn(buf, "\n")] = '\0';
		if (_strlen(buf) == 0)
			continue;
		if (_white(buf) == 1)
			continue;
		_check(buf, fnm);
	}
	free(buf);
	return (0);

}

