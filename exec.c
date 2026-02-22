#include "shell.h"

/**
 * print_not_found - Print "not found" error like sh (with argv[0])
 * @prog: argv[0]
 * @line_no: input line number
 * @cmd: command name
 */
void print_not_found(const char *prog, unsigned long line_no, const char *cmd)
{
	fprintf(stderr, "%s: %lu: %s: not found\n", prog, line_no, cmd);
}

/**
 * exec_cmd - Execute a command (fork + execve)
 * @av: argument vector
 * @prog: argv[0]
 * @line_no: line number
 * @envp: environment
 *
 * Return: exit status
 */
int exec_cmd(char **av, const char *prog, unsigned long line_no, char **envp)
{
	pid_t pid;
	int st;
	char *path = NULL;

	if (!av || !av[0])
		return (0);

	if (strchr(av[0], '/'))
	{
		if (access(av[0], X_OK) != 0)
		{
			print_not_found(prog, line_no, av[0]);
			return (127);
		}
		path = strdup(av[0]);
	}
	else
	{
		path = resolve_path(av[0], envp);
	}

	if (!path)
	{
		print_not_found(prog, line_no, av[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		free(path);
		perror(prog);
		return (1);
	}

	if (pid == 0)
	{
		execve(path, av, envp);
		perror(prog);
		_exit(126);
	}

	free(path);

	if (waitpid(pid, &st, 0) == -1)
	{
		perror(prog);
		return (1);
	}

	if (WIFEXITED(st))
		return (WEXITSTATUS(st));

	return (1);
}
