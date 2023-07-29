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
	if (shell_env(command, fnm) == 1)
		tell = 1;

	if (_contains_pipe(command) == 1)
	{
		tell = 1;
		handle_pipe(command, fnm);
	}
	if (tell == 0)
	{
		tkn = tokenie(command, " ");
		path = path_handler(tkn[0]);
		if (path == NULL)
		{
			path = _strdup(tkn[0]);
			execute_command(tkn, path, fnm, "fork");
		}

		else
			execute_command(tkn, path, fnm, "fork");
		free(path);
		free_func(tkn);
	}
}
int shell_env(char *command, char *fnm)
{
	char **tkn = NULL;

	if (_strncmp(command, "setenv", 6) == 0)
	{
		if(command[6] == ' ' || command[6] == '\0')
		{
			tkn = tokenie(command, " ");
			_setenv(tkn, fnm);
			free_func(tkn);
			return (1);
		}
	}
	if (_strncmp(command, "unsetenv", 8) == 0)
	{
		if(command[8] == ' ' || command[8] == '\0')
		{
			tkn = tokenie(command, " ");
			_unsetenv(tkn);
			free_func(tkn);
			return (1);
		}
	}
	if (_strncmp(command, "env", 3) == 0)
	{
		if(command[3] == ' ' || command[3] == '\0')
		{
			_env();
			return (1);
		}
	}
	return (0);
}
