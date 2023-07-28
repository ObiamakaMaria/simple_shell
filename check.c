#include "shell.h"
/**
 * _check - function that runs the shell
 * @command: the user input
 * @fnm: the name of the executable file
 * return: return void
 */

void _check(char *command, char *fnm)
{
	char **tkn = NULL;
	char *path = NULL;
	int tell = 0;

	count_quotes(command);
	if (_strncmp(command, "exit", 4) == 0)
	{
		tell = 1;
		if (command[4] == ' ' || command[4] == '\0')
			builtins(command, fnm);
	}


	if (tell == 0)
	{
		tkn = tokenie(command, " ");
		path = path_handler(tkn[0]);
		if (path == NULL)
		{
			path = _strdup(tkn[0]);
			execute_command(tkn, path, fnm);
		}

		else
			execute_command(tkn, path, fnm);
		free(path);
		free_func(tkn);
	}
}

