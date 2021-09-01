#include "mimibash.h"

char	**add_n(char **args)
{
	int		i;
	int		n;
	char	**tmp;

	i = 0;
	while (args[i] != NULL)
		i++;
	n = i;
	i = 0;
	tmp = malloc((n + 2) * sizeof(char *));
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
