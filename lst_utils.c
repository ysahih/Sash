#include "minishell.h"

t_tokenize	*ft_lstlast(t_tokenize *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_tokenize **lst, t_tokenize *new)
{
	t_tokenize	*last_node;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
    last_node->next->previous = last_node;
}


void   create_node(t_tokenize	**lst, char *s, int operator)
{
	t_tokenize	*node;

	node = malloc(sizeof(t_tokenize));
	node->type = operator;
	node->str = s;
	// printf("%c<<\n", *(node->str+ 10975238) );
	// if (operator == 2)
	// 	free(s);
    node->previous = NULL;
	node->next = NULL;
    ft_lstadd_back(lst, node);
}