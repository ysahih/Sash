#include "minishell.h"

void	builtin_cmds(char *s)
{
	if (!strcmp(s, "exit"))
		exit(0); 
}


t_tokenize	*create_node(t_tokenize	*lst, char *s, int operator)
{
	t_tokenize	*node;

	node = malloc(sizeof(t_tokenize));
	node->str = s;
	node->type = operator;
	node->previous = NULL;
	node->next = NULL;
	ft_lstadd_back(lst, node);
	return (node);
}

// t_tokenize	*link_nodes(char *line, t_operators operators)
// {
// 	t_tokenize	*node;
// 	int	i;

// 	i = 0;
// 	while (*line)
// 	{
// 		while (*line == ' ')
// 			line++;
// 		if (line[i] )
// 		line++;
// 	}
// 	return (node);
// }

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
	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}

void	tokenize(char *str)
{
	char	*wp;
	char *line;
	t_tokenize *node = NULL;

	line = str;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line == '|')
			create_node(node, "|", PIPE);
		if (*line == '>')
		{
			if (*line + 1 == '>')
				create_node(node, ">>", APPEND);
			else
				create_node(node, ">", OUTRED);
		}
		if (*line == '<')
		{
			if (*line + 1 == '<')
				create_node(node, "<<", HERDOC);
			else
				create_node(node, "<", INRED);
		}
		else
			node = create_node(node, "cmn", WORD);
		line++;
	}
	// link_nodes(str, operator);
}

int	main(int ac, char **av)
{
	char	*line;

	if (ac != 1)
		return (printf("program does not accept agruments"), 0);
	while (1)
	{
		line = readline("sh$ ");
		if (!line)
			break ;
		builtin_cmds(line);
		tokenize(line);


		if (*line)
			add_history(line);
	}
}