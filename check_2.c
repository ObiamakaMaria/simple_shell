#include "shell.h"
char *concatenate(char **arr, size_t size);
/**
 * buf_end - funciton that checks for repition of character
 * @command: the user input
 * Return: 0 on nothing, 1 on finding double of the character\\
 at the end of the input, 2 on finding three of the character consecutively
 */
int buf_end(char *command)
{
	char *r = NULL;
	int l;

	if (command[0] == '&')
		return (0);
	r = remove_w(command);
	l = _strlen(r);

	l--;

	if (r != NULL)
	{
		if (has_consecutive(r, '&'))
		{
			free(r);
			return (2);
		}
		if (r[l] == '&' && r[l - 1] == '&')
		{
			free(r);
			return (1);
		}
		free(r);
	}
	return (0);
}
/**
 * run_buf_end - function that execute base on buf_end return value
 * @cp: struct holding the executable file name and user input
 * @tmp: pointer to the adderes of a string that temporary hold\\
 the value of user input when on continous reading mode
 * @sta: condition for reading input prompt ">"
 * @state: condition for default prompt "$"
 * Return: void
 */
void run_buf_end(concatenate_pair cp, char **tmp, int *sta, int *state)
{
	int i = 1;



	if (buf_end(cp.buf) == 2)
		separator_error(cp.fnm, i, "\"&&\"");
	else
	{
		if (*tmp != NULL)
		free(*tmp);
		*tmp = _strdup(cp.buf);

		*sta = 1;
		*state = 1;

	}
}
/**
 * append_to_beginning - function that  append one string to \\
 the beginning of second string
 * @str1: the first and the base string i.e the string to accept\\
 other string
 * @str2: the second string
 * Return: void
 */

void append_to_beginning(char *str1, char *str2)
{
	size_t str1_len, str2_len, i;

	if (str1 != NULL && str2 != NULL)
	{

	str1_len = strlen(str1);
	str2_len = strlen(str2);

	for (i = str1_len + 1; i > 0; i--)
		str1[i + str2_len - 1] = str1[i - 1];

	for (i = 0; i < str2_len; i++)
		str1[i] = str2[i];
	}
}

