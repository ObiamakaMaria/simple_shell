#include "shell.h"
/**
 *  tokenie- This function helps to tokenize strings.
 * Description: In this function , the strtok helps to tokenize strings
 *  i : this is the variable to help iterate the loop.
 *
 * @command : This represents the arguement of the tokenize function
 * @delim: the delimiter for tokenization
 * Return: This function returns the  tokenized strings.
 */

char **tokenie(char *command, char *delim)
{
	int i = 0;
	int j;
	char *token;
	char **tokenize = NULL;
	char *cpy = _strdup(command);

	tokenize = malloc((ARGUMENT_MAX + 1) * sizeof(char *));
	if (tokenize == NULL)
	{
		free(cpy);
		return (NULL);
	}

	token = _strtok(cpy, delim);
	while (token != NULL && i < ARGUMENT_MAX)
	{
		tokenize[i] = _strdup(token);
		if (tokenize[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(tokenize[j]);
			free(tokenize);
			free(cpy);
			return (NULL);
		}
		token = _strtok(NULL, delim);
		i++;
	}
	free(cpy);
	tokenize[i] = NULL;
	return (tokenize);
}
