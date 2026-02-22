#include "shell.h"

/**
 * trim_line - Trim leading/trailing spaces/tabs and remove newline
 * @s: string to trim (modified in place)
 */
void trim_line(char *s)
{
	size_t i, start = 0, end;

	if (!s)
		return;

	/* remove trailing newline/carriage return */
	end = strlen(s);
	while (end > 0 && (s[end - 1] == '\n' || s[end - 1] == '\r'))
		s[--end] = '\0';

	/* skip leading spaces/tabs */
	while (s[start] == ' ' || s[start] == '\t')
		start++;

	if (start > 0)
	{
		for (i = 0; s[start + i]; i++)
			s[i] = s[start + i];
		s[i] = '\0';
	}

	/* trim trailing spaces/tabs */
	end = strlen(s);
	while (end > 0 && (s[end - 1] == ' ' || s[end - 1] == '\t'))
		s[--end] = '\0';
}
