#include "shell.h"
/**
 * has_c - function that check if it contains certain character
 * @str: the string to check
 * @s: the character to check
 * Return: 1 on true and 0 on false
 */

int has_c(const char *str, char s)
{
	int i = 0;
	int ret = 0;

	while (str[i] != '\0')
	{
		if (str[i] == s && str[i +1] == s)
		{
			ret = 1;
		}
		i++;
	}
	return (ret);

}

/**
 * remove_w - function that remove white space
 * @str: the string to remove from 
 * Return: NULL on failure the string without whitespace on success
 */
char *remove_w(const char *str)
{
	int j;
	int i;
	char *tem = NULL;
	char *tmp = NULL;
	int original_l;
	char w = ' ';

	tmp = strdup(str);
	original_l = strlen(tmp);
	tem = (char*) malloc(original_l + 1);
	if (tem == NULL)
	{
		free(tmp);
		return (NULL);
	}
	for (j = 0, i = 0; tmp[i] != '\0'; i++)
	{
		if (tmp[i] != w)
			tem[j++] = tmp[i];

	}
	tem[j] = '\0';

	free(tmp);
	return (tem);
}

