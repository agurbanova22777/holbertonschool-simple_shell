#include "shell.h"

/**
 * print_not_found - Print "not found" message
 * @prog: argv[0]
 * @line_no: line number
 * @cmd: command
 */
void print_not_found(const char *prog, unsigned long line_no, const char *cmd)
{
	fprintf(stderr, "%s: %lu: %s: not found\n", prog, line_no, cmd);
}

/**
 * get_cmd_path - Determine executable path for a command
 * @cmd: command name
 * @prog: argv[0]
 * @line_no: line number
 * @envp: environment
 *
 * Return: malloc'd path or NULL
 */
static char *get_cmd_path(const char *cmd, const char *prog,
		unsigned long line_no, char **envp)
{
	char *path;

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) != 0)
		{
			print_not_found(prog, line_no, cmd);
			return (NULL);
		}
		return (strdup(cmd));
	}

	path = resolve_path(cmd, envp);
	if (!path)
		print_not_found(prog, line_no, cmd);

	return (path);
}

/**
 * wait_child - Wait for child process
 * @pid: child pid
 * @prog: argv[0]
 *
 * Return: exit status
 */
static int wait_child(pid_t pid, const char *prog)
{
	int st;

	if (waitpid(pid, &st, 0) == -1)
	{
		perror(prog);
		return (1);
	}

	if (WIFEXITED(st))
		return (WEXITSTATUS(st));

	return (1);
}

/**
 * exec_cmd - Fork/exec a command with args
 * @av: argv tokens
 * @prog: argv[0]
 * @line_no: line number
 * @envp: environment
 *
 * Return: exit status
 */
int exec_cmd(char **av, const char *prog, unsigned long line_no, char **envp)
{
	pid_t pid;
	char *path;
	int status;

	path = get_cmd_path(av[0], prog, line_no, envp);
	if (!path)
		return (127);

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
	status = wait_child(pid, prog);
	return (status);
}
