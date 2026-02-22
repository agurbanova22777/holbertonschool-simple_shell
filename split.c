#include "shell.h"

/**
 * free_argv - Free argv array
 * @argv: NULL-terminated argv
 */
void free_argv(char **argv)
{
	size_t i;

	if (!argv)
		return;

	for (i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
}

/**
 * split_line - Split line into argv tokens (whitespace)
 * @line: input line (modified by strtok)
 *
 * Return: malloc'd argv or NULL
 */
char **split_line(char *line)
{
	char *tok, *copy;
	size_t count = 0, i = 0;
	char **argv;

	copy = strdup(line);
	if (!copy)
		return (NULL);

	tok = strtok(copy, " \t\r\n");
	while (tok)
	{
		count++;
		tok = strtok(NULL, " \t\r\n");
	}
	free(copy);

	if (count == 0)
		return (NULL);

	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);

	tok = strtok(line, " \t\r\n");
	while (tok)
	{
		argv[i] = strdup(tok);
		if (!argv[i])
		{
			while (i > 0)
				free(argv[--i]);
			free(argv);
			return (NULL);
		}
		i++;
		tok = strtok(NULL, " \t\r\n");
	}
	argv[i] = NULL;

	return (argv);
}
