#include "shell.h"
/**
 * _environs - function that set and unset environ, also print
 * @command: the user input
 * @fnm: the executable file name
 * Return: 1 on succes, 0 on failure
 */
int _environs(char *command, char *fnm)
{
	char **tkn = NULL;

	if (contains_exit(command, "setenv"))
	{
		tkn = tokenie(command, " ");
		_setenv(tkn, fnm);
		free_func(tkn);
		return (1);
	}
	if (contains_exit(command, "unsetenv"))
	{
		tkn = tokenie(command, " ");
		_unsetenv(tkn);
		free_func(tkn);
		return (1);
	}
	if (contains_exit(command, "env"))
	{
		_env();
		return (1);
	}
	return (0);
}
/**
 * separator_2 - continuation of _separator function in check.c
 * @command: the user input
 * @fnm: executable file name
 * @ptr: to check if the shell should enter continous reading state
 * @j: the condition set from _separtor function
 * Return: void
 */
void separator_2(char *command, char *fnm, int *ptr, int j)
{
	char **tkn = NULL;
	int mm = 1, i = 0;

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
				_check(tkn[i], fnm, ptr);
				i++;
			}

		}
		free_func(tkn);
	}
}
/**
 * _execution_to_shell - function that send command to the\\
 execution function "shell_with_path"
 * @command: user input
 * @fnm: the executable file name
 * Return: 1 on succes 0 on failure
 */
int _execution_to_shell(char *command, char *fnm)
{
	char *path = NULL, **tkn = NULL;

	tkn = tokenie(command, " ");
	path = path_handler(tkn[0]);
	if (path == NULL)
	{
		path = _strdup(tkn[0]);
		if (shell_with_path(tkn, path, fnm))
		{
			free(path);
			free_func(tkn);
			return (1);
		}
	}

	else
	{
		if (shell_with_path(tkn, path, fnm))
		{
			free(path);
			free_func(tkn);
			return (1);
		}
	}
	free(path);
	free_func(tkn);
	return (0);
}
/**
 * extra_main - continuation of main function
 * @cp: the struct containing the buf and other strings
 * @tmp: the temporary pointer to string, that holds the last\\
 command before encountering the continous reading mode
 * @sta: one of the state to check before printing the prompt\\
 or  continous reading mode prompt ">"
 * @state: second of the state to the above
 * Return: void
 */
void extra_main(concatenate_pair cp, char **tmp, int *sta, int *state)
{
	if (*tmp != NULL)
	{
		append_to_beginning(cp.buf, *tmp);
		free(*tmp);
		*tmp = NULL;
	}
	if (buf_end(cp.buf, '&') || buf_end(cp.buf, '|'))
		run_buf_end(cp, tmp, sta, state);
	else
	{
		*state = 0;
		_check(cp.buf, cp.fnm, state);
	}
}
