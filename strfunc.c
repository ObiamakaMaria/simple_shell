#include "shell.h"
/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: length
 */

int _strlen(const char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

/**
 * _strcspn - funct that gets a segment from  a string
 * @str1: the string to search
 * @str2: the character to search for
 * Return: the index of the character searached for
 */

int _strcspn(const char *str1, const char *str2)
{
	int count = 0;
	int i;
	int found;

	while (*str1 != '\0')
	{
		i = 0;
		found = 0;

		while (str2[i] != '\0')
		{
		if (str1[count] == str2[i])
		{
			found = 1;
			break;
		}
		i++;
		}
	if (found)
		break;
	count++;
	}
	return (count);
}

/**
 * _itoa - converts an integer to string
 * @value: the value of the integer to be converted
 * @buffer: the buffer to store the converted string
 *
 * Return: the int converted from the string
 */

void _itoa(int value, char *buffer)
{
	int i = 0, tmp; if (value == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
		return;
	}
	if (value < 0)
	{
		buffer[i++] = '-';
		value = -value;
	}
	tmp = value;
	while (tmp > 0)
	{
		tmp /= 10;
		i++;
	}
	buffer[i] = '\0';
	while (value > 0)
	{
		buffer[--i] = '0' + (value % 10);
		value /= 10;
	}
}

/**
 * _strcat - concatenate 2 strings
 * @dest: input
 * @src: input
 * Return: void
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * char *_strcpy - a function that copies the string pointed to by src
 * @dest: copy to
 * @src: copy from
 * Return: string
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;
	int j = 0;

	while (*(src + i) != '\0')
	{
		i++;
	}
	for ( ; j < i ; j++)
	{
		dest[j] = src[j];
	}
	dest[i] = '\0';
	return (dest);
}
