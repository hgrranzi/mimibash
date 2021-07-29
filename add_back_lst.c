#include "mimibash.h"

t_data *newlst(void)
{
	t_data *new;

	new = (t_data *)malloc(sizeof(t_data));
	if (!new)
		error_and_exit(NULL, NULL, 1);
	if (new)
	{
		new->builtin = 0;
		new->args = NULL;
		new->fd[0] = 0;
		new->fd[1] = 1;
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
t_data	*add_back_lst(t_data **lst, t_data *new)
{
	t_data *tmp;

	tmp = *lst;

	if (*lst == NULL)
		(*lst) = new;
	else
	{
		tmp = lastlst(*lst);
		tmp->next = new;
	}
	return(tmp);
}
