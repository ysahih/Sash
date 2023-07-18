#include "minishell.h"

t_lexer	*ft_lstlast(t_lexer *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*last_node;
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


void   create_node(t_lexer	**lst, char *s, int operator)
{
	t_lexer	*node;

	if (s == NULL)
		return ;
	node = malloc(sizeof(t_lexer));
	node->type = operator;
	node->str = s;
    node->previous = NULL;
	node->next = NULL;
    ft_lstadd_back(lst, node);
}