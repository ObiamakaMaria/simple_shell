#ifndef SHELL_H
#define SHELL_H
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syscall.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>

/* for keeping the shell running*/
#define ON 1
/* fixed buffer size*/
#define BUFFER_SIZE 1024
/* maximum number of arguments */
#define ARGUMENT_MAX 200
#define MAX_COMMAND_LENGTH 100
#ifndef O_RDONLY
#define O_RDONLY 0
#endif
/*temporary execute func */
void execute_command(char **tkn, char *command, char *fnm, char *det);
void _check(char *command, char *fnm);


void handle_sigint(int signum);
void count_quotes(char *str);
void handle_pipe(char *input, char *fnm);
extern char **environ;
extern char **dup_environ;
extern char *buf;
int is_file_exists(const char *filename);
void simple_shell(char **argg, char *path, char *fnm);
/* function that free arays */
void free_func(char **token);

/* shell with path environment*/
void shell_with_path(char **argg, char *path, char *fnm);

/* String Methods */
char *_strcpy(char *dest, const  char *src);
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
void _itoa(int value, char *buffer);
int _strncmp(const char *str1, const char *str2, size_t num);
int _strcspn(const char *str1, const char *str2);
void *_memcpy(void *dest, const void *src, size_t n);
int _white(const char *str);
int _contains_pipe(const char *input);
int _strcmp(const char *s1, char *s2);
char *_strtok(char *str, const char *delimiter);
char *_strchr(const char *s, char c);

/*custom getline function */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* shell related functions */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void builtins(char *command, char *fnm);
void exit_code(int status);
char **tokenie(char *command, char *delim);
char *isInPath(char *input);
char *custom_getline();
char  *path_handler(char *command);
char *get_env(const char *key);
char *_strdup(const char *str);
int is_executable(const char *path);

/*env builtins */
int _env(void);
int _setenv(char **args, char *fnm);
int _unsetenv(char **args);

#endif

