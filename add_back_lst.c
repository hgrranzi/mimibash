#include "minishell.h"

t_data *newlst(int built, char **args, int fd)
{
	t_data *new;

	new = (t_list *)malloc(sizeof(t_data))
	if (new)
	{
		new->builtin = built;
		new->args = args;
		new->fd = fd;
		new->next = NULL;
	}
	return (new);
}
t_data	*lastlst(t_data *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
t_data add_back_lst(t_data **lst, t_data *new)
{
	t_data *tmp;

	tmp = *lst;
	if (lst == NULL)
		return ;
	if (*lst == NULL)
		(*lst) = new;
	else
	{
		tmp = lastlst(*lst);
		tmp->next = new;
	}
}