#include "minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;
	

	i = 0;
	j = 0;
	while (dest[j] != '\0')
		j++;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	// printf("%s\n", dest);
	return (dest);
}

t_lexer	*rm_quote(t_lexer *cmdline)
{
	t_lexer	*node;
	t_lexer	*tmp;

	node = NULL;
	while (cmdline)
	{
		if (cmdline->type != DQUOTE && cmdline->type != SQUOTE)
			create_node(&node, cmdline->str, cmdline->type);
		cmdline = cmdline->next;
	}
	while (cmdline)
	{
		tmp = cmdline->next;
		free(cmdline);
		cmdline = tmp;
	}
	return (node);
}

t_lexer	*merge_word(t_lexer *cmd)
{
	t_lexer	*node;
	t_lexer	*tmp;

	node = NULL;
	if (!cmd)
		return NULL;
	while (cmd)
	{
		if (cmd->next && cmd->type == WORD && cmd->next->type == WORD)
		{
			create_node(&node, ft_strcat(cmd->str, cmd->next->str) , WORD);
			cmd = cmd->next->next;
		}
		if (!cmd)
			break ;
		else
		{
			create_node(&node, cmd->str, cmd->type);
			cmd = cmd->next;
		}
	}
	if (cmd)
		create_node(&node, cmd->str, cmd->type);
	while (cmd)
	{
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
	return (node);
}

t_lexer	*rm_space(t_lexer *cmd)
{
	t_lexer	*node;
	t_lexer	*tmp;

	node = NULL;
	while (cmd)
	{
		if (cmd->type != SPACE)
			create_node(&node, cmd->str, cmd->type);
		cmd = cmd->next;
	}
	while (cmd)
	{
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
	return(node);
}

void    parse(t_lexer *cmdline)
{
	t_lexer *cmd;

	cmd = rm_quote(cmdline);
	cmd = merge_word(cmd);
	cmd = rm_space(cmd);

	t_lexer	 *tmp = cmd;
	while (tmp)
	{
		printf("----|%s|--%d-\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}