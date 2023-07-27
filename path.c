#include "shell.h"

/**
 * get_env - func that gets environment variable
 * @key: they string of what to look for
 * Return: pointer to the found member
 */

char *get_env(const char *key)
{
	int i = 0;
	size_t k = _strlen(key);

	while (environ[i] != NULL)
	{

		if (_strncmp(environ[i], key, k) == 0 && environ[i][k] == '=')
			return (&environ[i][k + 1]);
		i++;
	}

	return (NULL);
}

/**
 * isInPath - func that checks for a command in path
 * @input: the user input to check
 * Return: the path found
 */

char *isInPath(char *input)
{

	char *path = get_env("PATH");
	char *token;
	char *path_command;
	char *path_copy;

	if (path == NULL)
		return (NULL);
	path_copy = _strdup(path);
	token = _strtok(path_copy, ":");

	while (token != NULL)
	{
		path_command = malloc(_strlen(token) + _strlen(input) + 2);

		_strcpy(path_command, token);
		_strcat(path_command, "/");
		_strcat(path_command, input);

		if (access(path_command, F_OK) == 0)
		{
			free(path_copy);
			return (path_command);
		}
		free(path_command);
		token = _strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * path_handler - func that handle the path
 * @input: user input
 * Return: pointer to the absolute path of input
 */

char *path_handler(char *input)
{
	char *token;
	char *path_command;
	char *cpy = _strdup(input);

	token = _strtok(cpy, " ");

	if (token == NULL)
	{
		free(cpy);
		return (NULL);
	}
	path_command = isInPath(token);
	if (path_command == NULL)
	{
		free(cpy);
		return (NULL);
	}
	free(cpy);
	return (path_command);
}

