/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:34:44 by ysahih            #+#    #+#             */
/*   Updated: 2023/07/23 18:31:42 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	event(void)
{
	return (0);
}

void	hd_sig(int sig)
{
	(void)sig;
	gl.rl = 1;
	rl_done = 1;
}

t_simple_cmd	*collect_scmds(t_lexer **cmdline, int i)
{
	t_simple_cmd	*cmd;

	cmd = create_scmd(*cmdline);
	while (*cmdline)
	{
		if ((*cmdline)->type == PIPE)
		{
			*cmdline = (*cmdline)->next;
			break ;
		}
		else if ((*cmdline)->type >= OUTRED && (*cmdline)->type <= APPEND)
			parse_red(cmdline, &cmd);
		else if ((*cmdline)->type == HERDOC)
			parse_hd(&cmd, cmdline);
		else if ((*cmdline)->type == WORD || (*cmdline)->type == -2)
		{
			cmd->str[i++] = (*cmdline)->str;
			(*cmdline) = (*cmdline)->next;
		}
	}
	return (cmd->str[i] = NULL, cmd);
}

t_lexer	*filter(t_all *all, t_lexer *cmdline)
{
	t_lexer	*cmd;

	cmd = rm_quote(cmdline);
	if (cmd->type == -2)
		cmd = cmd->next;
	if (!cmd || (cmd && cmd->type == WSPACE))
	{
		ft_putstr_fd("sash: : command not found\n", 2);
		gl.exit_status = 127;
		while (cmd && cmd->type != PIPE)
			cmd = cmd->next;
		if (cmd && cmd->type == PIPE)
			cmd = cmd->next;
	}
	cmd = expand_var(cmd, all->env);
	cmd = parse_wc(cmd);
	cmd = merge_word(cmd);
	cmd = rm_space(cmd);
	return (cmd);
}

void	parse(t_all *all, t_lexer *cmdline)
{
	t_simple_cmd	*scmd;
	t_lexer			*cmd;
	t_lexer			*tmp1;
	t_lexer			*tmp2;

	scmd = NULL;
	cmd = filter(all, cmdline);
	tmp1 = cmd;
	while (cmd)
		add_scmd(&scmd, collect_scmds(&cmd, 0));
	while (tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
	}
	all->cmd = scmd;
}
