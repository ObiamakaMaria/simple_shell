#include "shell.h"
/**
 * buf_end - funciton that checks for repition of character
 * @command: the user input
 * Return: 0 on nothing, 1 on finding double of the character\\
 at the end of the input, 2 on finding three of the character consecutively
 */
int buf_end(char *command)
{
	char *r = remove_w(command);
	int l = _strlen(r);

	l--;

	if (r != NULL)
	{
		if (has_consecutive(r, '&'))
		{
			free(r);
			return (2);
		}
		if (r[l] == '&' && r[l - 1] == '&')
		{
			free(r);
			return (1);
		}
		free(r);
	}
	return (0);
}
/**
 * run_buf_end - function that execute base on buf_end return value
 * @command: the user input
 * @fnm: the executable file
 * @sta: condition for reading input prompt ">"
 * @state: condition for default prompt "$"
 * Return: void
 */
void run_buf_end(char *command, char *fnm, int *sta, int *state)
{
	int i = 1;

	if (buf_end(command) == 2)
		separator_error(fnm, i, "\"&&\"");
	else
	{
		*sta = 1;
		*state = 1;
	}
}

