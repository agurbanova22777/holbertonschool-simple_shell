#include "shell.h"

/**
 * print_env - Print the current environment
 * @envp: environment
 */
void print_env(char **envp)
{
	size_t i;
	size_t len;

	if (!envp)
		return;

	for (i = 0; envp[i]; i++)
	{
		len = strlen(envp[i]);
		write(STDOUT_FILENO, envp[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
}
