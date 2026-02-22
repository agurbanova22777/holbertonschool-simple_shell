#include "shell.h"

/**
 * shell_loop - Read/execute loop
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
		char **av;

		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &cap, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line_no++;
		av = split_line(line);
		if (!av)
			continue;

		if (strcmp(av[0], "exit") == 0)
		{
			free_argv(av);
			break;
		}

		if (strcmp(av[0], "env") == 0)
		{
			print_env(envp);
			free_argv(av);
			continue;
		}

		status = exec_cmd(av, prog, line_no, envp);
		free_argv(av);
	}

	free(line);
	return (status);
}
