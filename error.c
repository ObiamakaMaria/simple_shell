#include "shell.h"

/**
 * get_int_length - Function to calculate the length of an integer
 * @num: the integer we are talking about
 * Return: the length of the  num or 1 if num is 0
 */
int get_int_length(int num)
{
	int len = 0;

	if (num == 0)
		return (1);

	while (num > 0)
	{
		len++;
		num /= 10;
	}

	return (len);
}

/**
 * int_to_string - Function to convert an integer to a string
 * @num: the number to be converted to string
 * @buffer: pointer to the string to store the converted
 * Return: void
 */
void int_to_string(int num, char *buffer)
{
	int len, i;

	if (num == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return;
	}

	len = get_int_length(num);

	for (i = len - 1; i >= 0; i--)
	{
		buffer[i] = num % 10 + '0';
		num /= 10;
	}

	buffer[len] = '\0';
}
/**
 * write_error_message - function that writes erroe to stderr
 * @fnm: the name of the executable file
 * @mm: the number of time a user enter wrong or error command
 * @path: the pointer to the user command
 * Return: -1 on failure, 1 on success
 */

int write_error_message(const char *fnm, int mm, const char *path)
{
	const char *error_msg = ": not found\n";
	char mm_str[10];
	char *error_string = NULL;
	int fnm_len = 0, mm_len = 0, path_len = 0, error_msg_len = 0;
	int total_length, index = 0, i;

	int_to_string(mm, mm_str);
	while (fnm[fnm_len] != '\0')
		fnm_len++;
	while (mm_str[mm_len] != '\0')
		mm_len++;
	while (path[path_len] != '\0')
		path_len++;
	while (error_msg[error_msg_len] != '\0')
		error_msg_len++;
	total_length = fnm_len + mm_len + path_len + error_msg_len + 3;
	error_string = (char *)malloc(total_length + 2);
	if (!error_string)
		return (-1);
	for (i = 0; i < fnm_len; i++)
		error_string[index++] = fnm[i];
	error_string[index++] = ':';
	error_string[index++] = ' ';
	for (i = 0; i < mm_len; i++)
		error_string[index++] = mm_str[i];
	error_string[index++] = ':';
	error_string[index++] = ' ';
	for (i = 0; i < path_len; i++)
		error_string[index++] = path[i];
	for (i = 0; i < error_msg_len; i++)
		error_string[index++] = error_msg[i];
	error_string[index] = '\0';
	write(2, error_string, total_length + 1);
	free(error_string);
	return (1);
}
/**
 * separator_error - function that writes erroe to stderr
 * @fnm: the name of the executable file
 * @mm: the number of time a user enter wrong or error command
 * @path: the pointer to the user command
 * Return: -1 on failure, 1 on success
 */
int separator_error(const char *fnm, int mm, const char *path)
{
	const char *err_1 = "Syntax error: ";
	const char *err_2 = " unexpected\n";
	char mm_s[10];
	char *error_string = NULL;
	int f_len = _strlen(fnm);
	int mm_len, p_len, err_1_l, err_2_l;
	int total_length, index = 0, i;

	int_to_string(mm, mm_s);
	mm_len = _strlen(mm_s);
	p_len = _strlen(path);
	err_1_l = _strlen(err_1);
	err_2_l = _strlen(err_2);
	total_length = f_len + mm_len + p_len + err_1_l + err_2_l + 4;
	error_string = (char *)malloc(total_length + 1);
	if (!error_string)
		return (-1);
	for (i = 0; i < f_len; i++)
		error_string[index++] = fnm[i];
	error_string[index++] = ':';
	error_string[index++] = ' ';
	for (i = 0; i < mm_len; i++)
		error_string[index++] = mm_s[i];
	error_string[index++] = ':';
	error_string[index++] = ' ';
	for (i = 0; i < err_1_l; i++)
		error_string[index++] = err_1[i];
	for (i = 0; i < p_len; i++)
		error_string[index++] = path[i];
	for (i = 0; i < err_2_l; i++)
		error_string[index++] = err_2[i];
	error_string[index] = '\0';
	write(2, error_string, total_length);
	free(error_string);
	return (1);
}
