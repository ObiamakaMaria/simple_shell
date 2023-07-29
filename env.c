#include "shell.h"


/**
 * _env - Prints the current environment.
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 */
int _env(void)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}
	return (0);
}

/**
 * _setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell
 * @fnm: the executable file name
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int _setenv(char **args, char *fnm)
{
	char *env_var = NULL, *new_value, **new_environ;
	char *ptr;
	size_t size;
	int index;

	if (!args[0] || !args[1] || !contains_e(args[1]))
	{
		_env();
		return (-1);
	}
	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (-1);
	ptr = new_value;
	_strcpy(ptr, args[1]);
	env_var = get_env(args[0]);
	if (env_var)
	{
		_strcpy(env_var, new_value);
		free(new_value);
		return (0);
	}
	/* Find the size of the current environment */
	for (size = 0; environ[size]; size++)
		;
	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		perror(fnm);
		free(new_value);
		return (-1);
	}
	for (index = 0; environ[index]; index++)
		new_environ[index] = strdup(environ[index]);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * Return: zero on success else return -1
 */

int _unsetenv(char **args)
{
	char *env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!args[1])
		return (-1);
	env_var = get_env(args[1]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (-1);

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (env_var == environ[index])
		{
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
