#include "shell.h"

/**
 * print_not_found - Print "not found" error like sh (with argv[0])
 * @prog: argv[0]
 * @line_no: line number
 * @cmd: command
 */
void print_not_found(const char *prog, unsigned long line_no, const char *cmd)
{
	fprintf(stderr, "%s: %lu: %s: not found\n", prog, line_no, cmd);
}

/**
 * run_one_word - Run a one-word command via execve
 * @prog: argv[0]
 * @line_no: line number
 * @cmd: command (no args)
 * @envp: environment
 *
 * Return: exit status
 */
int run_one_word(const char *prog, unsigned long line_no, char *cmd, char **envp)
{
	pid_t pid;
	int st;
	char *av[2];

	av[0] = cmd;
	av[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror(prog);
		return (1);
	}

	if (pid == 0)
	{
		execve(cmd, av, envp);
		print_not_found(prog, line_no, cmd);
		_exit(127);
	}

	if (waitpid(pid, &st, 0) == -1)
	{
		perror(prog);
		return (1);
	}

	if (WIFEXITED(st))
		return (WEXITSTATUS(st));

	return (1);
}
