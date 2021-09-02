#include "mimibash.h"
char	*getstrquote(char *str, int i, int j)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	tmp1 = ft_substr(str, 0, i);
	tmp2 = ft_substr(str, i + 2, j - i - 2);
	tmp3 = ft_strdup(str + j + 1);
	tmp4 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	tmp1 = NULL;
	free(tmp2);
	tmp2 = NULL;
	tmp1 = ft_strjoin(tmp4, tmp3);
	free(tmp4);
	tmp4 = NULL;
	free(tmp3);
	tmp3 = NULL;
	return (tmp1);
}