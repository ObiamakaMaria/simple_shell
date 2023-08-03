#include "shell.h"
/**
 * _comment - the functin that take care of comment #
 * @command: user input
 * @fnm: the executable file
 * Return: void
 */
void _comment(char *command, char *fnm)
{
	char **tkn = NULL, *ret = remove_w(command);
	int i = 1;

	tkn = tokenie(command, "#");
	if (tkn != NULL)
	{
		if (ret[0] != '#')
			_check(tkn[0], fnm, &i);


	}
	free_func(tkn);
	free(ret);
}
