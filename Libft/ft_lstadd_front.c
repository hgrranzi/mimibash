#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	ft_lstlast(new)->next = tmp;
	*lst = new;
}
