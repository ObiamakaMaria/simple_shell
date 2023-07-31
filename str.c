#include "shell.h"

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to be located.
 *
 * Return: If c is found - a pointer to the first occurence.
 *         If c is not found - NULL.
 */

char *_strchr(const char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}

	return (NULL);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: Positive byte difference if s1 > s2
 *         0 if s1 = s2
 *         Negative byte difference if s1 < s2
 */
int _strcmp(const char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}
/**
 * contains_m - function that check for multiple column
 * @str: the string to check
 * Return: 1 on truee and 0 on false
 */
int contains_m(const char *str)
{
	int count = 0;
	int i;

	if (str == NULL || str[0] == '\0')
		return (0);

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ';')
		{
			count++;
			if (count > 1)
				return (1);
		}
	}

	return (0);
}
/**
 * logical_b - function that check for the first occurrence of character
 * @c: the character to check
 * @command: the string to check
 * Return: the index of the first c
 */
int logical_b(const char *command, char c)
{
	int i = 0;
	int found_c = 0;
	int j;

	while (command[i] != '\0')
	{
		if (command[i] == c)
		{
			j = i - 1;
			while (j >= 0 && command[j] == ' ')
				j--;
			if (j < 0 && !found_c)
				return (i);
			else
				return (-1);
		}
		else if (command[i] != ' ')
			found_c = 1;
		i++;
	}

	return (-1);
}
/**
 * has_consecutive - function that check for consecutive character 3x
 * @str: the string to check
 * @c: the character to check
 * Return: 1 if found else zero
 */
int has_consecutive(const char *str, char c)
{
	int count = 1, i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == c)
		{
			count++;
			if (count == 3)
				return (1);
		}
		else
			count = 0;
	}

	return (0);
}
