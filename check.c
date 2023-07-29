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
/**
 * shell_env - functino that run builtin commands
 * @command: the user input
 * @fnm: the executable file name
 * Return: 1 if command contains them 0 if not
 */
int shell_env(char *command, char *fnm)
{
	char **tkn = NULL;

	if (_strncmp(command, "setenv", 6) == 0)
	{
		if (command[6] == ' ' || command[6] == '\0')
		{
			tkn = tokenie(command, " ");
			_setenv(tkn, fnm);
			free_func(tkn);
			return (1);
		}
	}
	if (_strncmp(command, "unsetenv", 8) == 0)
	{
		if (command[8] == ' ' || command[8] == '\0')
		{
			tkn = tokenie(command, " ");
			_unsetenv(tkn);
			free_func(tkn);
			return (1);
		}
	}
	if (_strncmp(command, "env", 3) == 0)
	{
		if (command[3] == ' ' || command[3] == '\0')
		{
			_env();
			return (1);
		}
	}
	if (_strchr(command, ';') != NULL)
	{
		
		_separator(command, fnm);
		return (1);

	}
	return (0);
}
/**
 * _separator - the function that runs command separator
 * @fnm: the executable file name
 * Return: void
 */
void _separator(char *command, char *fnm)
{
	int i = 0, j = 0;
	static int mm = 1;
	char *ret = NULL, *patt = NULL;
	char **tkn = NULL, **tkn_2 = NULL;

	if (has_c(command, ';') == 1)
		j = 1;
	else
	{
		ret = remove_w(command);
		if (ret != NULL)
		{
			if (has_c(ret, ';') == 1)
				j = 1;
			else if (ret[0] == ';')
				j = 1;
				
		}
		free(ret);
	}

	if (j)
	{
		if (contains_m(command))
			separator_error(fnm, mm, ";;");
		else
			separator_error(fnm, mm, ";");
	}
	else if (!j)
	{
		tkn = tokenie(command, ";");
		if (tkn != NULL)
		{
			while (tkn[i] != NULL)
			{
				tkn_2 = tokenie(tkn[i], " ");
				patt = path_handler(tkn_2[0]);
				if (patt == NULL)
				{
					patt = _strdup(tkn_2[0]);
					execute_command(tkn_2, patt, fnm, "fork");
				}
				if (patt != NULL)
					execute_command(tkn_2, patt, fnm, "fork");
				free_func(tkn);
				i++;
			}
		}
	}




}
