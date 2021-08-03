#include "mimibash.h"

int ft_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return(1);
	return (0);
}

// char *parse_dollar(char *str, int *i, char **env)
// {
// 	char *tmp1;
// 	char *tmp2;
// 	char *tmp3;
// 	char *tmp4;
// 	int j;
// 	int n;
// 	int k;
// 	int m;

// 	k = 0;
// 	j = (*i);
// 	while(str[++(*i)] != '\0' )
// 	{
// 		if (!ft_key(str[(*i)]))
// 			break;
// 	}
// 	tmp1 = ft_substr(str, j + 1, (*i) - j - 1);
// 	tmp2 = ft_substr(str, 0, j);
// 	tmp4 = ft_strdup(str + (*i));
// 	tmp1 = ft_strjoin(tmp1, "=");
// 	n = ft_strlen(tmp1);
// 	while (env[k] != NULL)
// 	{
// 		if ((tmp3 = ft_strnstr(env[k], tmp1, n)))
// 			tmp2 = ft_strjoin(tmp2, tmp3 + n);
// 		k++;
// 	}
// 	free(tmp1);
// 	free(tmp3);
// 	tmp2 = ft_strjoin(tmp2, tmp4);
// 	free (tmp4);
// 	return (tmp2);
// }



// char **shielding(char **input, char **envp)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (input[i] != NULL)
// 	{
// 		j = 0;
// 		while(input[i][j] !='\0')
// 		{

// 			if (input[i][j] == '$')
// 				input[i] = parse_dollar(input[i], &j, envp);
// 			if (input[i][j] == '\\')
// 				input[i] = parse_slash(input[i], &j);
// 			if (input[i][j] == '\'')
// 				input[i] = parse_single_quote(input[i], &j);
// 			if (input[i][j] == '\"')
// 				input[i] = parse_double_quote(input[i], &j, envp);
// 			j++;

// 		}
// 		// printf("%s\n", input[i]);
// 		i++;
// 	}
// 	return (input);
// }
void print_struct(t_data **data)
{
	t_data *tmp;
	tmp = *data;
	while (tmp !=NULL)
	{
		printf("builtin: %d\n", tmp->builtin);
		printf("fd[0]: %d\n", tmp->fd[0]);
		printf("fd[1]: %d\n", tmp->fd[1]);
		int i = 0;
		while(tmp->args[i] != NULL)
		{
			printf("args[%d]: %s\n", i, tmp->args[i]);
			i++;
		}
		tmp = tmp->next;
	}
}
void arr_free(char **array)
{
	int i;
	
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
void parser(char *input, char **envp, t_data **data, int exit_status)
{
	int i;
	int j;
	int n;
	char **str;
	char **tmp;
	t_data *last;
	i = 0;
	str = pipesplit(input);
	
	while(str[i] !=NULL)
	{
		last = add_back_lst(data, newlst());
		str[i] = parse_redir(str[i], last->fd, envp);
		tmp = new_split(str[i], ' ');
		// j = 0;
		// while(tmp[j] != NULL)
		// {
		// 	printf("%s\n", tmp[j]);
		// 	j++;
		// }
		free(str[i]);
		last->args = shielding(tmp, envp, exit_status);
		get_builtins(&last->args[0], &last->builtin);
		if (last->builtin == 1 && ft_strncmp(last->args[1], "-n", 3))
			last->args = add_n(last->args, last->builtin);
		else if (last->builtin == 1 && !ft_strncmp(last->args[1], "-n", 3))
		 	last->args = remove_n(last->args, last->builtin);

		last->args=check_builtins(last);
		i++;
	}
	free(str);
	// print_struct(data);
}
