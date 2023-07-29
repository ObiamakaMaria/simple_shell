#include "shell.h"
#include <fcntl.h>

/**
 * shell_with_path - function that implement fork and excve for commands
 * @argg: the arrays of commands and arguments
 * @path: the absolute path of a short command
 * @fnm: the  name of the executable file for the shell
 * return: void
 */
void shell_with_path(char **argg, char *path, char *fnm)
{
	pid_t pid;
	int status;
	static int mm = 1;

	if (is_file_exists(path) || !is_executable(path))
	{
		if (write_error_message(fnm, mm, path) == -1)
		{
			free(path);
			free_func(argg);
			exit(0);
		}
		mm++;
		exit(27);
	}
	else if (is_executable(path))
	{
		pid = fork();
		if (pid == -1)
		{
			perror("failed to fork");
			exit(1);
		}
		else if (pid == 0)
		{
			if (execve(path, argg, environ) == -1)
			{
				free(path);
				free_func(argg);
				perror(fnm);
				exit(1);
			}
		}
		else
		{
			do
				waitpid(pid, &status, WUNTRACED);
			while	(!WIFEXITED(status) && !WIFSIGNALED(status));
		}

	}
}

/**
 * simple_shell - function that implement fork and excve for commands
 * @argg: the arrays of commands and arguments
 * @path: the absolute path of a short command
 * @fnm: the  name of the executable file for the shell
 * return: void
 */
void simple_shell(char **argg, char *path, char *fnm)
{
	if (is_file_exists(path) || !is_executable(path))
	{

		free(path);
		free_func(argg);
		exit(27);
	}
	else if (is_executable(path))
	{

		if (execve(path, argg, environ) == -1)
		{
			free(path);
			free_func(argg);
			perror(fnm);
		}
	}
}

/**
 * execute_command - function that call simple_shell or shell_with_path
 * @tkn: pointer to an array of strings for file execution
 * @command: the comand to execute
 * @fnm: the shell executable name
 * @det: it is the determinant whether to call fork or not
 * return: void
 */
void execute_command(char **tkn, char *command, char *fnm, char *det)
{


	if (strcmp(det, "nofork") == 0)
	{
		simple_shell(tkn, command, fnm);
	}
	else if (strcmp(det, "fork") == 0)
		shell_with_path(tkn, command, fnm);
}
/**
 * is_executable - funct to check if command is executable
 * @path: the command to check
 * Return: 1 on success, 0 on failure
 */

int is_executable(const char *path)
{
	if (access(path, X_OK) != -1)
		return (1);
	else
		return (0);
}

/**
 * free_func - function that free arrays of strings
 * @token: the array to be freed
 * Return: void
 */

void free_func(char **token)
{
	int i = 0;

	while (token[i] != NULL)
		free(token[i++]);
	free(token);
}


