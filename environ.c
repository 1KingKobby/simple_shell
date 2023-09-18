#include "shell.h"

/**
 * my_env - Prints the current environment.
 * @info: Pointer to a structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * Return: Always 0
 */
int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env_value - Gets the value of an environment variable.
 * @info: Pointer to a structure containing potential arguments. Used to maintain
 * @name: The environment variable name.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - Initializes a new environment variable or modifies an existing one.
 * @info: Pointer to a structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * Return: 0 on success, 1 on error.
 */
int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Removes an environment variable.
 * @info: Pointer to a structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * Return: 0 on success, 1 on error.
 */
int my_unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list.
 * @info: Pointer to a structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * Return: 0 on success, 1 on error.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
