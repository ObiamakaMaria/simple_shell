#include "shell.h"

/**
 * main - the main function
 * @argc: the argument count plus the ame of file
 * @argv: arrays of arguments and name of file
 * Return: 0 on succes
 */
int main(int argc, char **argv)
{
	size_t n = 0;
	int state = 0, sta = 0;
	char *tmp = NULL;
	concatenate_pair cp;

	(void)argc;
	cp.buf = NULL;
	cp.fnm = argv[0];
	signal(SIGINT, handle_sigint);
	while (ON)
	{
		if (!state)
		write(STDIN_FILENO, "$ ", 2);
		if (state && sta)
			write(STDIN_FILENO, "> ", 2);
		fflush(stdout);
		if (_getline(&cp.buf, &n, stdin) == -1)
		{
			write(STDIN_FILENO, "\n", 1);
			break;
		}
		cp.buf[_strcspn(cp.buf, "\n")] = '\0';
		if (_strlen(cp.buf) == 0)
		{
			if (!sta)
			state = 0;
			continue;
		}
		if (_white(cp.buf) == 1)
		{
			if (!sta)
			state = 0;
			continue;
		}
		extra_main(cp, &tmp, &sta, &state);
	}
	if (tmp != NULL)
		free(tmp);
	free(cp.buf);
	return (0);
}
