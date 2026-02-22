#include "shell.h"

/**
 * shell_loop - Main REPL loop (one-word commands only)
 * @prog: argv[0]
 * @envp: environment
 *
 * Return: status of last command
 */
int shell_loop(const char *prog, char **envp)
{
	char *line = NULL;
	size_t cap = 0;
	ssize_t nread;
	unsigned long line_no = 0;
	int interactive = isatty(STDIN_FILENO);
	int status = 0;

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		nread = getline(&line, &cap, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line_no++;
		trim_line(line);

		if (line[0] == '\0')
			continue;

		status = run_one_word(prog, line_no, line, envp);
	}

	free(line);
	return (status);
}
