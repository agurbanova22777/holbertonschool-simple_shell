#include "shell.h"

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * @envp: environment
 *
 * Return: exit status
 */
int main(int ac, char **av, char **envp)
{
	(void)ac;
	return (shell_loop(av[0], envp));
}
