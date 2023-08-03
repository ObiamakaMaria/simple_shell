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
/**
 * double_pipe - funciton that tokenize base on double pipe delimeter
 * @input: the input to tokenize
 * Return: pointer to arrays of strings or NULL
 */
char **double_pipe(const char *input)
{
	char *delimiter = "||";
	int num = count_tokens(input, delimiter);
	char **tokens = (char **)malloc((num + 1) * sizeof(char *));

	if (tokens == NULL)
	{
		return (NULL);
	}

	extract_tokens(tokens, input, delimiter);
	tokens[num] = NULL;
	return (tokens);
}
/**
 * count_tokens - function that count the input of the user\\
 for tokenization
 * @input: the user input to count
 * @delimiter: the delimeter for tokenization
 * Return: the number of strings to contian in the array
 */
int count_tokens(const char *input, const char *delimiter)
{
	char *copy_input = _strdup(input);
	char *ptr = copy_input;
	int count = 0;
	char *token, prev_char;

	while (1)
	{
		token = _strstr(ptr, delimiter);
		if (token == NULL)
		{
			count++;
			break;
		}
		if (token != ptr)
		{
			prev_char = *(token - 1);
			if (prev_char != '|')
			{
				count++;
			}
		}
		token += 2;
		ptr = token;
	}

	free(copy_input);
	return (count);
}
/**
 * extract_tokens - functino that extract token from input
 * @input: the user input
 * @tokens: the array of strings created from the input
 * @d: the delimiter for tokenization
 * Return: void
 */
void extract_tokens(char **tokens, const char *input, const char *d)
{
	char *copy_input = _strdup(input);
	char *ptr = copy_input;
	int index = 0;
	char *token, prev_char;

	while (1)
	{
		token = _strstr(ptr, d);
		if (token == NULL)
		{
			tokens[index] = _strdup(ptr);
			break;
		}

		if (token != ptr)
		{
			prev_char = *(token - 1);
			if (prev_char != '|')
			{
				*token = '\0';
				tokens[index] = _strdup(ptr);
				index++;
			}
		}

		token += 2;
		ptr = token;
	}

	free(copy_input);
}
