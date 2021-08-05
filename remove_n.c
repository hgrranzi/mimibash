#include "mimibash.h"
char **remove_n(char **args, int built)
{
	int i;
	char **tmp;

	i = 0;
	while(args[i] != NULL)
		i++;
	tmp = malloc(sizeof(char *) * (i));
	// printf("remove_n:%p\n", tmp);
	tmp[0] = args[0];
	i = 2;
	while (args[i] != NULL)
	{
		tmp[i - 1] = ft_strdup(args[i]);
		free(args[i]);
		i++;
	}
	free(args[1]);
	free(args);
	tmp[i-1] = NULL;
	return (tmp);
}
char **add_n(char **args, int builtin)
{
	int i;
	int n;
	char **tmp;

	i = 0;
	while (args[i] != NULL)
		i++;
	n = i;
	i = 0;
	tmp = malloc((n + 2)*sizeof(char *));
	// printf("add_n:%p\n", tmp);
	while (i < n)
	{
		tmp[i] = ft_strdup(args[i]);
		free(args[i]);
		i++;
	}
	free(args);
	tmp[i++] = ft_strdup("\n");
	tmp[i] = NULL;
	return (tmp);
}