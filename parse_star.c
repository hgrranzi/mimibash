#include "mimibash.h"
int	check_quotes(char *str)
{
	int	j;

	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '\"' || str[j] == '\'' || str[j] == '\\' || str[j] == '$')
			return (0);
		j++;
	}
	return (1);
}

int	massive_size(char **mas)
{
	int	i;

	i = 0;
	while (mas && mas[i] != NULL)
		i++;
	return (i);
}

char	**new_star_massive(char **massive, int i, char **old_tmp)
{
	char	**tmp;
	t_list	*data;
	t_list	*ptr;
	int		j;

	j = 0;
	data = check_wildcard(massive[i]);
	if (data == NULL)
		return (masjoin(old_tmp, massive[i]));
	ptr = data;
	tmp = malloc(sizeof(char *) * (ft_lstsize(data) + massive_size(old_tmp) + 1));
	while (old_tmp && old_tmp[j])
	{
		tmp[j] = ft_strdup(old_tmp[j]);
		j++;
	}
	free_arr(old_tmp);
	old_tmp = NULL;
	while (data != NULL)
	{
		tmp[j] = ft_strdup(data->content);
		data = data->next;
		j++;
	}
	tmp[j] = NULL;
	ft_lstclear(&ptr, free);
	return (tmp);
}

char	**masjoin(char **str1, char *str2)
{
	char	**tmp;
	int		j;

	j = 0;
	tmp = malloc(sizeof(char *) * (massive_size(str1) + 2));
	while (str1 && str1[j])
	{
		tmp[j] = ft_strdup(str1[j]);
		j++;
	}
	tmp[j] = ft_strdup(str2);
	j++;
	tmp[j] = NULL;
	free_arr(str1);
	str1 = NULL;
	return (tmp);
}

char	**parse_star(char ***str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while ((*str)[i] != NULL)
	{
		if (check_quotes((*str)[i]))
		{
			if (ft_strchr((*str)[i], '*'))
				tmp = new_star_massive(*str, i, tmp);
			else
				tmp = masjoin(tmp, (*str)[i]);
		}
		else
			tmp = masjoin(tmp, (*str)[i]);
		i++;
	}
	if (tmp)
	{
		free_arr(*str);
		(*str) = NULL;
		return (tmp);
	}
	else
		return (*str);
}
