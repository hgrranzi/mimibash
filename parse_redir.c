#include "mimibash.h"
int create_fd(char *str, int flag)
{
	int fd;

	if (flag == 1)
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (flag == 2)
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (flag == 3)
		fd = open(str, O_RDONLY, 0644);
	if (fd == -1)
		error_and_exit(str, NULL, 0);
	// printf("fd: %d\n", fd);
	return (fd);
}

char *redir(char *str, int *i, int *fd, int flag, char **env)
{
	int j;
	int n;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	j = (*i);
	(*i)++;
	while (str[(*i)] == ' ')
		(*i)++;
	n = (*i) - j;
	while(str[(*i)] != '\0' )
	{
		if (str[(*i)] == '$')
			str = parse_dollar(str, i, env);
		if (str[(*i)] == '\"')
			str = parse_double_quote(str, i, env);
		if (!ft_key(str[(*i)]))
			break;
		(*i)++;
	}
	tmp1 = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + n, (*i) - j - 1);
	tmp3 = ft_strdup(str + (*i));
	tmp1 = ft_strjoin(tmp1, tmp3);
	(*fd) = create_fd(tmp2, flag);
	if((*fd) == -1)
	{
		free(tmp2);
		tmp2 = NULL;
	}
	free(tmp3);
	(*i)= j - 1;
	return(tmp1);

}
void check_open_quote(char c, int *n, int *k, int *i)
{
	if (c == '\"' && (*n)%2 == 0)
	{
		(*k)++;
		(*i)++;
	}
	if (c == '\'' && (*k)%2 == 0)
	{
		(*n)++;
		(*i)++;
	}
}
char *parse_redir(char *str, int *fd, char **envp)
{
	int i;
	int k;
	int n;

	i = 0;
	k = 0;
	n = 0;
	while(str[i] != '\0' && fd[0] != -1 && fd[1] != -1)
	{
		check_open_quote(str[i], &n, &k, &i);
		if((k%2) == 0 && (n%2) == 0)
		{
			if(str[i] == '>' && str[i + 1] == '>')
			{
				if (fd[1] > 1)
					close(fd[1]);
				str = redir(str, (&i + 1), &fd[1], 1, envp);
			}
			if (str[i] == '>' && str[i + 1] != '>')
			{
				if (fd[1] > 1)
					close(fd[1]);
				str = redir(str, &i, &fd[1], 2, envp);
			}
			if (str[i] == '<' && str[i + 1] != '<')
			{
				if (fd[0] > 0)
					close(fd[0]);
				str = redir(str, &i, &fd[0], 3, envp);
			}
		}
		i++;
	}
	return (str);
}
