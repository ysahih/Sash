#include "minishell.h"



t_lexer	*rm_quote(t_lexer *cmdline)
{
	t_lexer	*node;

	node = NULL;
	while (cmdline)
	{
		if (cmdline->type != DQUOTE && cmdline->type != SQUOTE)
		{
			puts("store");
			ft_lstadd_back(&node, cmdline);
		}
		// else if (cmdline->type == DQUOTE || cmdline->type == SQUOTE)
		// {
		// 	puts("skip");
		cmdline = cmdline->next;
		// // }
		// else if (!cmdline)
		// 	break ;
		// puts("here");
	}
	return (node);

}

void    parse(t_lexer *cmdline)
{
	t_lexer *node;

	node = rm_quote(cmdline);
	// t_lexer	 *tmp = node;
	// while (tmp)
	// {
	// 	printf("----|%s|--%d-\n", tmp->str, tmp->type);
	// 	tmp = tmp->next;
	// }
}