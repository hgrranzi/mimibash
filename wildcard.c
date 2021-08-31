#include "mimibash.h"

int	are_equal(char *s1, char *s2)
{
	if (*s1 != '\0' && *s2 == '*')
		return (are_equal(s1 + 1, s2) || are_equal(s1, s2 + 1));
	if (*s1 == '\0' && *s2 == '*')
		return (are_equal(s1, s2 + 1));
	if (*s1 == *s2 && *s1 != '\0')
		return (are_equal(s1 + 1, s2 + 1));
	if (*s1 == *s2 && *s1 == '\0')
		return (1);
	return (0);
}

t_list	*find_equals(char *str, DIR *opened_wd)
{
	t_list			*equals;
	struct dirent	*wd_info;
	char			*filename;

	equals = NULL;
	while (1)
	{
		wd_info = readdir(opened_wd);
		if (!wd_info)
			break ;
		if (wd_info->d_name[0] != '.' && are_equal(wd_info->d_name, str))
		{
			filename = ft_strdup(wd_info->d_name);
			if (!filename)
				error_and_exit(NULL, NULL, 1);
			ft_lstadd_back(&equals, ft_lstnew(filename));
		}
	}
	return (equals);
}

t_list	*check_wildcard(char *str)
{
	t_list	*equals;
	char	*wd;
	DIR		*opened_wd;

	wd = getcwd(NULL, 0);
	if (!wd)
		error_and_exit(NULL, NULL, 1);
	free(wd);
	opened_wd = opendir(wd);
	if (!opened_wd)
		error_and_exit(NULL, NULL, 1);
	equals = find_equals(str, opened_wd);
	closedir(opened_wd);
	return (equals);
}

/*
int	main(int argc, char **argv)
{
	t_list	*equals;
	t_list	*equals_p;

	if (argc != 2)
		return (1);
	equals = check_wildcard(argv[1]);
	if (!equals)
		printf("No files equal argv[1]");
	else
	{
		equals_p = equals;
		while (equals_p)
		{
			printf("%s", equals_p->content);
			if (equals_p->next)
				printf(" ");
			equals_p = equals_p->next;
		}
		printf("\n");
	}
	return (0);
}
*/
