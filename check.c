#include "shell.h"
/**
 * _check - function that runs the shell
 * @command: the user input
 * @fnm: the name of the executable file
 * @ptr: to check if to print the prompt again
 * return: return void
 */

void _check(char *command, char *fnm, int *ptr)
{
	char **tkn = NULL;
	char *path = NULL;
	int tell = 0;

	*ptr = 0;
	count_quotes(command);
	if (_strncmp(command, "exit", 4) == 0)
	{
		tell = 1;
		if (command[4] == ' ' || command[4] == '\0')
			builtins(command, fnm);
	}
	if (shell_env(command, fnm, ptr) == 1)
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
 * @ptr: check the _check function for this description
 * Return: 1 if command contains them 0 if not
 */
int shell_env(char *command, char *fnm, int *ptr)
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

		_separator(command, fnm, ptr);
		return (1);

	}
	if (_strchr(command, '&') != NULL)
	{

		logical_and(command, fnm, ptr);
		return (1);

	}
	return (0);
}
/**
 * _separator - the function that runs command separator
 * @fnm: the executable file name
 * @ptr: check the _check function above for description of this
 * @command: user input
 * Return: void
 */
void _separator(char *command, char *fnm, int *ptr)
{
	int i = 0, j = 0;
	static int mm = 1;
	char *ret = NULL;
	char **tkn = NULL;

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
			separator_error(fnm, mm, "\";;\"");
		else
			separator_error(fnm, mm, "\";\"");
	}
	else if (!j)
	{
		tkn = tokenie(command, ";");
		if (tkn != NULL)
		{
			while (tkn[i] != NULL)
			{
				_check(tkn[i], fnm, ptr);
				i++;
			}

		}
		free_func(tkn);
	}



}
/**
 * logical_and - the function that runs command separator
 * @fnm: the executable file name
 * @ptr: check _check function for description of this argument
 * @command: user input
 * Return: void
 */
void logical_and(char *command, char *fnm, int *ptr)
{
	int j = 0, k = 0, l = 0;
	static int mm = 1;
	int lg_i;

	lg_i = logical_b(command, '&');

	if (lg_i != -1)
	{
		j = 1;
		if (command[lg_i] == '&' && command[lg_i + 1] == '&')
			k = 1;
		if (command[lg_i] == '&' && command[lg_i + 1] != '&')
			l = 1;
	}
	if (j)
	{
		if (k)
			separator_error(fnm, mm, "\"&&\"");
		else if (l)
			separator_error(fnm, mm, "\"&\"");
	}
	if (!j)
	{
		not_j(command, fnm, ptr);
	}
}
/**
 * not_j - function that execute logical & if !j cas
 * @fnm: the name of the executable file
 * @command: user input
 * @ptr: check the _check function for description
 * Return: void
 */
void not_j(char *command, char *fnm, int *ptr)
{
	char **tkn = NULL, *ret = remove_w(command);
	int len = _strlen(ret), i = 0;

	len--;
	tkn = tokenie(command, "&");
	if (tkn != NULL)
	{
		while (tkn[i] != NULL)
		{
			if (ret != NULL)
			{
				if (ret[len] == '&' && ret[len - 1] != '&')
				{
					_check(tkn[i], fnm, ptr);
					*ptr = 1;
					break;
				}

			}

			_check(tkn[i], fnm, ptr);
			i++;
		}

	}
	if (ret != NULL)
		free(ret);
	free_func(tkn);
}
