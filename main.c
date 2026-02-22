#include "shell.h"

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: exit status
 */
int main(int ac, char **av)
{
	(void)ac;
	return (shell_loop(av[0]));
}
