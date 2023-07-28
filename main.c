/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:20:17 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/25 09:59:25 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(t_all *all)
{
	t_simple_cmd	*tmp;

	while (all->cmd)
	{
		tmp = all->cmd;
		all->cmd = all->cmd->next;
		if (tmp->str)
		{
			ft_freee(tmp->str);
		}
		free(tmp);
	}
}

void	core(t_all *all)
{
	char	*line;
	t_lexer	*cmd;

	while (true)
	{
		g_gl.rl = 0;
		line = readline("minishell>$ ");
		if (!line)
			return (printf("exit\n"), free_enex(all->env), free_enex(all->exp));
		if (*line)
			add_history(line);
		else
		{
			free(line);
			continue ;
		}
		cmd = tokenize(line);
		if (!analyze_syntax(cmd))
			continue ;
		parse(all, cmd);
		exec(all);
		free_cmds(all);
	}
	free_enex(all->env);
	free_enex(all->exp);
}

int	main(int ac, char **av, char **env)
{
	t_all	all;

	if (ac != 1 || av[1])
		return (printf("program does not accept agruments\n"), 0);
	set_env(&all, env);
	sig_handler();
	core(&all);
	return (g_gl.exit_status);
}
