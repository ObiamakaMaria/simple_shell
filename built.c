#include "shell.h"

/**
 * builtins - funct that implement builtins command
 * @command: the input of the user
 * @fnm: the name of the programme
 * Return: void
 */

void builtins(char *command, char *fnm)
{
	char *token;
	char *end_ptr;
	long status;

	token = _strtok(command, " \t\n");
	if (token == NULL)
		perror(fnm);

	else
	{
		token = _strtok(NULL, " \t\n");
		if (token == NULL)
		{
			free(command);
			exit_code(0);
		}
		else
		{
			status = strtol(token, &end_ptr, 10);
			if (*end_ptr != '\0' || end_ptr == token)
			{
				write(STDOUT_FILENO, "exit status not a number: ", 27);
				write(STDOUT_FILENO, token, _strlen(token));
				write(STDOUT_FILENO, "\n", 2);
				free(command);
				exit_code(1);
			}
			else
			{
				free(command);
				exit((int)status);
			}

		}
	}
}

/**
 * exit_code - code that run exit built in
 * @status: status code
 * Return: void
 */
void exit_code(int status)
{
	exit(status);
}

