#include "shell.h"
/**
 * _check - function that runs the shell
 * @command: the user input
 * @fnm: the name of the executable file
 * @ptr: to check if to print the prompt again
 * Return: 0 on succes, 1 on argument failure
 */
int _check(char *command, char *fnm, int *ptr)
{
	int tell = 0;

	*ptr = 0;
	count_quotes(command);
	if (contains_exit(command, "exit"))
	{
		tell = 1;
		builtins(command, fnm);
	}
	if (shell_env(command, fnm, ptr) == 1)
		tell = 1;

	if (_contains_pipe(command) == 1 && _strstr(command, "||") == NULL)
	{
		tell = 1;
		handle_pipe(command, fnm);
	}
	if (tell == 0)
	{
		if (_execution_to_shell(command, fnm))
			return (1);
	}
	return (0);
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

	if (_environs(command, fnm))
		return (1);
	if (_strchr(command, ';') != NULL)
	{

		_separator(command, fnm, ptr);
		return (1);

	}
	if (_strchr(command, '&') != NULL)
	{

		logical_and(command, fnm, ptr, '&');
		return (1);

	}
	if (_strstr(command, "||") != NULL)
	{

		logical_and(command, fnm, ptr, '|');
		return (1);

	}
	if (_strstr(command, "#") != NULL)
	{
		_comment(command, fnm);
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
	int j = 0;
	char *ret = NULL;

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
	separator_2(command, fnm, ptr, j);
}
/**
 * logical_and - the function that runs command separator
 * @fnm: the executable file name
 * @ptr: check _check function for description of this argument
 * @c: the character wheter '&' or '|'
 * @command: user input
 * Return: void
 */
void logical_and(char *command, char *fnm, int *ptr, char c)
{
	int j = 0, k = 0, l = 0;
	static int mm = 1;
	int lg_i;

	lg_i = logical_b(command, c);

	if (lg_i != -1)
	{
		j = 1;
		if (command[lg_i] == c && command[lg_i + 1] == c)
			k = 1;
		if (command[lg_i] == c && command[lg_i + 1] != c)
			l = 1;
	}
	if (j)
	{
		if (k)
		{
			if (c == '&')
				separator_error(fnm, mm, "\"&&\"");
			else
				separator_error(fnm, mm, "\"||\"");
		}
		else if (l)
		{
			if (c == '&')
				separator_error(fnm, mm, "\"&\"");
			else
				separator_error(fnm, mm, "\"|\"");
		}

	}
	if (!j)
	{
		not_j(command, fnm, ptr, c);
	}
}
/**
 * not_j - function that execute logical & if !j cas
 * @fnm: the name of the executable file
 * @command: user input
 * @ptr: check the _check function for description
 * @c: the delimeter
 * Return: void
 */
void not_j(char *command, char *fnm, int *ptr, char c)
{
	char **tkn = NULL, *ret = remove_w(command);
	int len = _strlen(ret), i = 0, k = 0;

	len--;
	if (c == '&')
		tkn = tokenie(command, "&");
	else
		tkn = double_pipe(command);
	if (tkn != NULL)
	{
		while (tkn[i] != NULL)
		{
			if (ret != NULL)
			{
				if (ret[len] == '&' && ret[len - 1] != '&')
				{
					_check(tkn[i], fnm, ptr);
					*ptr = 1, k = 1;
				}
			}
			if (!k)
			{
				if (c == '|')
				{
					if (!_check(tkn[i], fnm, ptr))
						break;
				}
				else
				{
					if (_check(tkn[i], fnm, ptr))
						break;
				}
			}
			i++;
		}
	}
	if (ret != NULL)
		free(ret);
	free_func(tkn);
}
