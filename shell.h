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
/**
 * struct concatenate_pair - struct that holds buf concatenation\\
 to contiue reading inputing if the shell is in a reading state ">"\\
 and concatenate the new input with the previous input before the \\
 string enter the continous reading state when it encouters any of \\
 this characters: "&&, ||, |" at the end of the input
 * @buf: the first user input before entering the reading state
 * @fnm: the executable file name
 */
typedef struct concatenate_pair
{
	char *buf;
	char *fnm;
} concatenate_pair;
/*temporary execute func */
void execute_command(char **tkn, char *command, char *fnm, char *det);
int _check(char *command, char *fnm, int *ptr);


void handle_sigint(int signum);
void count_quotes(char *str);
extern char **environ;
extern char **dup_environ;
extern char *buf;
int is_file_exists(const char *filename);
void simple_shell(char **argg, char *path, char *fnm);
void handle_pipe(char *input, char *fnm);
/* function that free arays */
void free_func(char **token);

/* shell with path environment*/
int shell_with_path(char **argg, char *path, char *fnm);

/* String Methods */
char *_strcpy(char *dest, const  char *src);
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
void _itoa(int value, char *buffer);
int _strncmp(const char *str1, const char *str2, size_t num);
int _strcspn(const char *str1, const char *str2);
void *_memcpy(void *dest, const void *src, size_t n);
int _white(const char *str);
int _strcmp(const char *s1, char *s2);
int has_consecutive(const char *str, char c);
void append_to_beginning(char *str1, char *str2);
char *_strtok(char *str, const char *delimiter);
char *_strchr(const char *s, char c);
char *_strstr(const char *haystack, const char *needle);
char **double_pipe(const char *input);
int count_tokens(const char *input, const char *delimiter);
void extract_tokens(char **tokens, const char *input, const char *d);
int contains_exit(const char *input, char *exit_str);
void int_to_string(int num, char *buffer);
int get_int_length(int num);
int write_error_message(const char *fnm, int mm, const char *path);
int _contains_pipe(const char *input);
int contains_e(const char *str);
int has_c(const char *str, char s);
char *remove_w(const char *str);
int contains_m(const char *str);
int logical_b(const char *command, char c);

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
int separator_error(const char *fnm, int mm, const char *path);
void logical_and(char *command, char *fnm, int *ptr, char c);
void not_j(char *command, char *fnm, int *ptr, char c);
int buf_end(char *command, char c);
void run_buf_end(concatenate_pair cp, char **tmp, int *sta, int *state);
/*env builtins */
int _env(void);
int _setenv(char **args, char *fnm);
int _unsetenv(char **args);
int shell_env(char *command, char *fnm, int *ptr);
int _environs(char *command, char *fnm);
int shell_cd(char **args, char *fnm);
void _separator(char *command, char *fnm, int *ptr);
void separator_2(char *command, char *fnm, int *ptr, int j);
int _execution_to_shell(char *command, char *fnm);
void extra_main(concatenate_pair cp, char **tmp, int *sta, int *state);
/* comment function */
void _comment(char *command, char *fnm);
#endif
