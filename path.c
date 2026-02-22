#include "shell.h"

/**
 * get_env - Get value of an env var
 * @name: variable name
 * @envp: environment
 *
 * Return: pointer to value inside envp, or NULL
 */
char *get_env(const char *name, char **envp)
{
	size_t i, nlen;

	if (!name || !envp)
		return (NULL);

	nlen = strlen(name);

	for (i = 0; envp[i]; i++)
	{
		if (strncmp(envp[i], name, nlen) == 0 && envp[i][nlen] == '=')
			return (envp[i] + nlen + 1);
	}
	return (NULL);
}

/**
 * resolve_path - Resolve cmd using PATH
 * @cmd: command without '/'
 * @envp: environment
 *
 * Return: malloc'd full path or NULL
 */
char *resolve_path(const char *cmd, char **envp)
{
	char *path, *copy, *dir, *full;
	size_t a, b;

	path = get_env("PATH", envp);
	if (!path || !*path)
		return (NULL);

	copy = strdup(path);
	if (!copy)
		return (NULL);

	dir = strtok(copy, ":");
	while (dir)
	{
		a = strlen(dir);
		b = strlen(cmd);

		full = malloc(a + 1 + b + 1);
		if (full)
		{
			memcpy(full, dir, a);
			full[a] = '/';
			memcpy(full + a + 1, cmd, b);
			full[a + 1 + b] = '\0';

			if (access(full, X_OK) == 0)
			{
				free(copy);
				return (full);
			}
			free(full);
		}
		dir = strtok(NULL, ":");
	}

	free(copy);
	return (NULL);
}
