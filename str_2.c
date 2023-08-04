#include "shell.h"
/**
 * _strstr - function that search for a string within a string
 * @haystack: the base string to search from
 * @needle: the string to search for
 * Return: null if not fuound, the base string if found
 */
char *_strstr(const char *haystack, const char *needle)
{
	const char *h;
	const char *n;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		h = haystack;
		n = needle;

		while (*n != '\0' && *h == *n)
		{
			h++;
			n++;
		}

		if (*n == '\0')
			return ((char *)haystack);
		haystack++;
	}

	return (NULL);
}
