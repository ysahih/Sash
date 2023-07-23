#include "../../minishell.h"

void	empty_quotes(t_lexer **cmdline, t_lexer **node)
{
	t_lexer	*cmd;

	cmd = *cmdline;
	if (!cmd->next)
		return ;
	if (cmd->type == DQUOTE && cmd->next->type == DQUOTE)
	{
		create_node(node, ft_strdup(""), -2, 0);
		cmd = cmd->next;
		cmd = cmd->next;
	}
	if (!cmd || !cmd->next)
		return ;
	if (cmd->type == SQUOTE && cmd->next->type == SQUOTE)
	{
		create_node(node, ft_strdup(""), -2, 0);
		cmd = cmd->next;
		cmd = cmd->next;
	}
	*cmdline = cmd;
}

t_lexer	*rm_quote(t_lexer *cmdline)
{
	t_lexer	*node;

	node = NULL;
	while (cmdline)
	{
		empty_quotes(&cmdline, &node);
		if (!cmdline)
			break ;
		if (cmdline->type != DQUOTE && cmdline->type != SQUOTE)
			create_node(&node, cmdline->str, cmdline->type, 0);
		cmdline = cmdline->next;
	}
	return (node);
}

void	join_words(t_lexer **node, t_lexer *cmd, char *str)
{
	while (cmd)
	{
		while (cmd && (cmd->type == WORD || cmd->type == -2))
		{
			str = ft_strjoin(str, cmd->str);
			cmd = cmd->next;
		}
		create_node(node, str, WORD, 0);
		str = NULL;
		if (!cmd)
			break ;
		else 
		{
			create_node(node, cmd->str, cmd->type, 0);
			cmd = cmd->next;
		}
	}
	if (cmd)
		create_node(node, cmd->str, cmd->type, 0);

}

t_lexer	*merge_word(t_lexer *cmd)
{
	t_lexer	*node;
	char 	*str;

	str = NULL;
	node = NULL;
	if (!cmd)
		return NULL;
	join_words(&node, cmd, str);
	return (node);
}