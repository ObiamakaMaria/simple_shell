#include "shell.h"

/**
 * main - the main function
 * @argc: the argument count plus the ame of file
 * @argv: arrays of arguments and name of file
 * Return: 0 on succes
 */

int main(int argc, char **argv)
{
	char *buf = NULL, *fnm = argv[0];
	size_t n = 0;
	int state = 0, sta = 0;

	(void)argc;

	signal(SIGINT, handle_sigint);
	while (ON)
	{
		if (!state)
		write(STDIN_FILENO, "$ ", 2);
		if (state && sta)
			write(STDIN_FILENO, "> ", 2);
		fflush(stdout);
		if (_getline(&buf, &n, stdin) == -1)
		{
			write(STDIN_FILENO, "\n", 1);
			break;
		}
		buf[_strcspn(buf, "\n")] = '\0';
		if (_strlen(buf) == 0)
		{
			if (!sta)
			state = 0;
			continue;
		}
		if (_white(buf) == 1)
		{
			if (!sta)
			state = 0;
			continue;
		}
		if (buf_end(buf))
		run_buf_end(buf, fnm, &sta, &state);
		else
		{
			state = 0;
			_check(buf, fnm, &state);
		}
	}
	free(buf);
	return (0);

}

