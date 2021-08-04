#include "mimibash.h"

char	*take_last_arg(t_data **head_data)
{
	int		i;
	char	*last_arg;

	i = 0;
	if ((*head_data)->next == NULL)
	{
		while ((*head_data)->args[i + 1])
			i++;
		if ((*head_data)->builtin == EXPORT)
		{
			if (i == 0)
				last_arg = strdup((*head_data)->args[i]);
			else
				last_arg = strndup((*head_data)->args[i], index_char((*head_data)->args[i], '='));
		}
		else if ((*head_data)->args[i][0] != '\n')
			last_arg = strdup((*head_data)->args[i]);
		else
			last_arg = strdup((*head_data)->args[i - 1]);
	}
	else
		last_arg = strdup("\0");
	return (last_arg);
}

void	update_underscore(t_data **head_data, char ***envp)
{
	char	*last_arg;
	char	**args;

	last_arg = take_last_arg(head_data);
	if (last_arg == NULL)
		error_and_exit(NULL, NULL, 1);
	args = malloc(3 * sizeof(char *));
	if (!args)
		error_and_exit(NULL, NULL, 1);
	args[0] = strdup("\0");
	args[1] = aka_strjoin("_=", last_arg);
	args[2] = NULL;
	free(last_arg);
	if (!args[0] || !args[1])
		error_and_exit(NULL, NULL, 1);
	exec_export((*head_data)->fd, args, envp);
	free_arr(args);
}
