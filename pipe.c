#include "shell.h"

/**
 * execute_single_command - function to execute a single command
 * @tkk: array of command tokens
 * @fnm: the name of the program
 *
 */

void execute_single_command(char **tkk, char *fnm)
{
	char *patt = path_handler(tkk[0]);

	if (patt != NULL)
		execute_command(tkk, patt, fnm, "nofork");
	if (patt == NULL)
	{
		patt = _strdup(tkk[0]);
		execute_command(tkk, patt, fnm, "nofork");
	}
}

/**
 * execute_with_pipe - function to execute a command with pipe
 * @command: the command to be executed
 * @fd_in: input file descriptor
 * @fnm: the name of the program
 */

void execute_with_pipe(char *command, int fd_in, char *fnm)
{
	char **tkk = tokenie(command, " ");
	pid_t pid;
	int pipe_fd[2];
	int status;
	int i = 0;


	pipe(pipe_fd); /* Create a pipe */
	pid = fork();

	if (pid == 0)
	{ /* Child process */
		close(pipe_fd[0]); /* Close the read end of the pipe */
		if (tkk[i + 1] != NULL)
	/* Issue: 'commands' and 'i' are not declared */
			dup2(pipe_fd[1], STDOUT_FILENO);
		if (i > 0)
			dup2(fd_in, STDIN_FILENO);

		execute_single_command(tkk, fnm);
		free_func(tkk);
		exit(1);
	}
	else
	{ /* Parent process */
		close(pipe_fd[1]);
		/* Close the write end of the pipe */
		waitpid(pid, &status, 0);
		/* Wait for the child process to finish */
		fd_in = pipe_fd[0];
		/* Set the input for the next command */
	}
}

/**
 * handle_pipe - function that handles chaining command with pipe
 * @input: the input of the user
 * @fnm: the name of the program
 */

void handle_pipe(char *input, char *fnm)
{
	char **commands = NULL;
	int i = 0;
	int pipe_fd[2];
	int fd_in = 0;

	commands = tokenie(input, "|");
	while (commands[i] != NULL)
	{
		pipe(pipe_fd); /* Create a pipe */
		execute_with_pipe(commands[i], fd_in, fnm);
		i++;
	}
	free_func(commands);
}
