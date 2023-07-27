#include "shell.h"

/**
 * _strdup - funct that copy to new memory space
 * @str: character
 * Return: 0 on succes
 */

char *_strdup(const char *str)
{
	char *cpy;
	int i;
	int j;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
		i++;
	cpy = malloc(sizeof(char) * (i + 1));
	if (cpy == NULL)
		return (NULL);
	for (j = 0; str[j] != '\0'; j++)
		cpy[j] = str[j];
	cpy[j] = '\0';
	return (cpy);
}

/**
 * _strncmp - func that compares two strings
 * @str1: the first string of comparison
 * @str2: the second string of comparison
 * @num: use to track the differnce in the string
 * Return: an integer
 */

int _strncmp(const char *str1, const char *str2, size_t num)
{
	while (num > 0)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		else if (*str1 == '\0')
			return (0);
		str1++;
		str2++;
		num--;
	}
	return (0);
}

/**
 * _memcpy - a function that copy memory of a variable
 * @dest: the destination of the copied memory
 * @src: the source variable to copy from
 * @n: number of bytes to copy
 * Return: pointers to the destination memory address
 */

void *_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	const unsigned char *s = src;
	unsigned char *d = dest; for (i = 0; i < n; i++)
		d[i] = s[i];
	return (dest);
}
/**
 * _white - a function that checks for only whitespace
 * @str: the argument
 * Return: return 1 if found else return 0 if not found
 */

int _white(const char *str)
{
	while (*str != '\0')
	{
		if (*str != ' ' && *str != '\t')
			return (0);
	str++;
	}
	return (1);
}
