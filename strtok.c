#include "shell.h"

/**
 * _strtok - function that separate string by delimeter
 * @str: the string to be separated
 * @delimiter: it could be space letter or any character
 * Return: it return null on failure but the separated token on success
 */
char *_strtok(char *str, const char *delimiter)
{
	static char *next_token;  /* Keeps track of the next token */
	char *token;

	if (str != NULL)
		next_token = str;

	/* Check if the next token exists */
	if (next_token == NULL || *next_token == '\0')
		return (NULL);

	/* Find the start of the token (skip leading delimiters) */
	token = next_token;
	while (*token != '\0' && _strchr(delimiter, *token) != NULL)
		token++;

	/* If the end of the string is reached, there are no more tokens */
	if (*token == '\0')
	{
		next_token = NULL;
		return (NULL);
	}

	/* Find the end of the token */
	next_token = token;
	while (*next_token != '\0' && _strchr(delimiter, *next_token) == NULL)
		next_token++;

	/* Null-terminate the token and update the next_token pointer */
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}
	else
		next_token = NULL;

	return (token);
}

