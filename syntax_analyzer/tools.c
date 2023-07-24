/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:34:32 by ysahih            #+#    #+#             */
/*   Updated: 2023/07/24 18:29:43 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	pipe_checker(t_lexer *cmd, int i)
{
	if (i && cmd->type == WSPACE && cmd->next == NULL)
		return (false);
	if (!i && cmd->type == WSPACE && cmd->previous == NULL)
		return (false);
	else if (cmd->next && cmd->previous)
	{
		if (i && cmd->type == WSPACE && cmd->next)
			cmd = cmd->next;
		else if (!i && cmd->type == WSPACE && cmd->previous)
			cmd = cmd->previous;
	}
	if (i)
		return ((cmd->type >= VAR && cmd->type <= HERDOC) || cmd->type == -1);
	return ((cmd->type >= VAR && cmd->type <= DQUOTE) || cmd->type == -1);
}

void	print_err(char *s)
{
	ft_putstr_fd("sash: syntax error near unexpected token '", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	g_gl.exit_status = 258;
}

bool	pipe_analyze(t_lexer *cmd)
{
	bool	flag;

	flag = true;
	if (cmd->next == NULL || cmd->previous == NULL)
		flag = false;
	else if (cmd->next && cmd->previous)
	{
		flag *= pipe_checker(cmd->next, 1);
		flag *= pipe_checker(cmd->previous, 0);
	}
	if (!flag)
	{
		print_err("|");
		return (false);
	}
	return (true);
}

bool	analyze_quote(t_lexer **node, int flag)
{
	t_lexer	*cmd;

	cmd = *node;
	if (!cmd->next)
	{
		ft_putstr_fd("sash: syntax error: unexpected end of file\n", 2);
		g_gl.exit_status = 258;
		return (false);
	}
	cmd = cmd->next;
	while (cmd && cmd->type != flag)
		cmd = cmd->next;
	*node = cmd;
	if (!cmd)
	{
		ft_putstr_fd("sash: syntax error: unexpected end of file\n", 2);
		g_gl.exit_status = 258;
		return (false);
	}
	return (true);
}

bool	red_analyze(t_lexer *cmd)
{
	if (cmd->next && cmd->next->type == WSPACE)
		cmd = cmd->next;
	if (!cmd->next || cmd->next->type > DQUOTE || cmd->next->type < VAR)
	{
		if (cmd->next)
			print_err(cmd->next->str);
		else
			print_err("newline");
		return (false);
	}
	return (true);
}
