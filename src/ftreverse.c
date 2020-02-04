
#include "../inc/ft_ls.h"

t_files		*reverse_order_files(t_files *start)
{
	t_files	*curr;
	t_files	*next;
	t_files	*prev;

	curr = start;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return (prev);
}