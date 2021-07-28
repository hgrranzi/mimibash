#include "mimibash.h"
int create_fd(char *str, int flag)
{
	int fd;

	if (flag == 1)
	{
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (flag == 2)
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (flag == 3)
		fd = open(str, O_RDONLY, 0644);
	// if (fd == -1)
	// 	Ошибка
	return (fd);
}

char *redir(char *str, int *i, int *fd, int flag)
{
	int j;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	j = (*i);
	while (str[(*i)] == ' ')
		(*i)++;
	while(str[++(*i)] != '\0')
	{
		if (str[(*i)] != '_' && !ft_key(str[(*i)]))
			break;
	}
	tmp1 = ft_substr(str, j + 1, (*i) - j - 1);
	tmp2 = ft_substr(str, 0, j);
	tmp3 = ft_strdup(str + (*i));
	tmp2 = ft_strjoin(tmp2, tmp3);
	free(tmp3);
	(*fd) = create_fd(tmp1, flag);
	if((*fd) == -1)
	{
		free(tmp2);
		tmp2 = NULL;
	}
	free (tmp1);
	(*i) = j - 1;
	return (tmp2);
}

char *parse_redir(char *str, int *fd)
{
	int i;

	i = 0;
	while(str[i] != '\0' && fd[0] != -1 && fd[1] != -1)
	{
		if(str[i] == '>' && str[i + 1] == '>')
			str = redir(str, (&i + 1), &fd[1], 1);
		if (str[i] == '>' && str[i + 1] != '>')
			str = redir(str, &i, &fd[1], 2);
		if (str[i] == '<' && str[i + 1] != '<')
			str = redir(str, &i, &fd[0], 3);
		i++;
	}
	printf("redir: %s\n", str);
	return (str);
}
