#include "shell.h"

char *tp(char **cmd);
/**
 * handle_sigint - function that register signals
 * @signum: the signal number
 * Return: void
 */
void handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		write(STDIN_FILENO, "\n$ ", 3);
	}
}
