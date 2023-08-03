#include "shell.h"
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
