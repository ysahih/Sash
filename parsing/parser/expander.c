/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:34:50 by ysahih            #+#    #+#             */
/*   Updated: 2023/07/24 17:01:04 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_var(t_var *var, char *str)
{
	char	*val;

	val = NULL;
	if (!strcmp("?", str))
	{
		val = ft_itoa(gl.exit_status);
		free(str);
		return (val);
	}
	while (var)
	{
		if (!strcmp(var->key, str))
		{
			val = ft_strdup(var->val);
		}
		var = var->next;
	}
	if (val == NULL)	
		val = ft_strdup("");
	free(str);
	return (val);
}

void	hd_var(t_lexer **node, t_lexer **cmdline)
{
	t_lexer	*cmd;

	cmd = *cmdline;
	create_node(node, cmd->str, cmd->type, 0);
	cmd = cmd->next;
	if (cmd && cmd->type == WSPACE)
	{
		create_node(node, cmd->str, cmd->type, 0);
		cmd = cmd->next;
	}
	if (cmd && cmd->type == VAR)
	{
		create_node(node, ft_strjoin("$", cmd->str), WORD, 0);
		cmd = cmd->next;
	}
	*cmdline = cmd;
}

t_lexer	*expand_var(t_lexer *cmd, t_var *var)
{
	t_lexer	*node;

	node = NULL;
	while (cmd)
	{
		if (cmd->type == HERDOC)
			hd_var(&node, &cmd);
		if (!cmd)
			break ;
		if (cmd->type == VAR)
		{
			create_node(&node, find_var(var, cmd->str), WORD, 0);
		}
		else
			create_node(&node, cmd->str, cmd->type, 0);
		cmd = cmd->next;
	}
	return (node);
}
