#include "../../minishell.h"

t_var	*last_var(t_var *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_simple_cmd	*last_cmd(t_simple_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_scmd(t_simple_cmd **lst, t_simple_cmd *new)
{
	t_simple_cmd	*last_node;
	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = last_cmd(*lst);
	last_node->next = new;
}

int	count_wd(t_lexer *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd->type != PIPE)
	{
		if ((cmd->type == WORD && !cmd->previous) ||
			(cmd->type == WORD && cmd->previous && cmd->previous->type <= WORD))
			i++;
		cmd = cmd->next;
	}
	return (i);
}

void	lst_var(t_var **var, char **s)
{
	t_var	*tmp;
	t_var	*last;

	if (!var || !s || !*s)
		return ;
	tmp = malloc(sizeof(t_var));
	tmp->key = ft_strdup(s[0]);
	tmp->val = ft_strdup(s[1]);
	tmp->next = NULL;
	if (*var == NULL)
	{
		*var = tmp;
		return ;
	}
	last = last_var(*var);
	last->next = tmp;
}