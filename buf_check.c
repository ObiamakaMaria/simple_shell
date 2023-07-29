#include "shell.h"
/**
 * is_file_exists - function that check if file name is the same with input
 * @filename: the input file to check
 * Return: 0 when not found but 1 when found
 */

int is_file_exists(const char *filename)
{
	int match = 0;
	struct dirent *entry;
	DIR *dir = opendir(".");

	if (dir == NULL)
	{
		perror("Unable to open directory");
		return (0);
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG && _strcmp(filename, entry->d_name) == 0)
		{
			match = 1;
			break;
		}
	}

	closedir(dir);
	return (match);
}

/**
 * remove_quotes - function to remove quotes from a string
 * @str: the string to remove quotes from
 */

void remove_quotes(char *str)
{
	int len = _strlen(str);
	int j = 0;
	int i; /* Declare 'i' outside the for-loop for compatibility*/

	for (i = 0; i < len; i++)
	{
		if (str[i] != '"' && str[i] != '\'')
			str[j++] = str[i];
	}

	str[j] = '\0';
}

/**
 *  count_quotes - function that checks for perfect quotes and removes them
 *  @str: the string to work on
 */

void count_quotes(char *str)
{
	int count = 0, condition_double = 0, condition_single = 0;
	int len = _strlen(str);
	int i; /* Declare 'i' outside the for-loop for compatibility*/

	for (i = 0; i < len; i++)
	{
		if (str[i] == '"')
			condition_double = 1;

		if (str[i] == '\'')
			condition_single = 1;

		if (condition_double && !condition_single)
		{
			if (str[i] == '"')
				count++;
		}
		else if (condition_single && !condition_double)
		{
			if (str[i] == '\'')
				count++;
		}
	}

	if (condition_double && !condition_single)
	{
		if (count % 2 == 0)
			remove_quotes(str);
	}
	else if (condition_single && !condition_double)
	{
		if (count % 2 == 0)
			remove_quotes(str);
	}
}

/**
 * _contains_pipe - a function that checks for pipe character
 * @input: the input the check
 * Return: return true if found
 */

int _contains_pipe(const char *input)
{
	if (_strchr(input, '|') != NULL)
		return (1);
	return (0);
}
