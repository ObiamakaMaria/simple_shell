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
	int state = 0;

	(void)argc;

	signal(SIGINT, handle_sigint);
	while (ON)
	{
		if (!state)
		write(STDIN_FILENO, "$ ", 2);
		fflush(stdout);
		if (_getline(&buf, &n, stdin) == -1)
		{
			write(STDIN_FILENO, "\n", 1);
			break;
		}
		buf[_strcspn(buf, "\n")] = '\0';
		if (_strlen(buf) == 0)
		{
			state = 0;
			continue;
		}
		if (_white(buf) == 1)
		{
			state = 0;
			continue;
		}
		_check(buf, fnm, &state);
	}
	free(buf);
	return (0);

}

