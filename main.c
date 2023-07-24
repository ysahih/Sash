/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:20:17 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/24 17:32:15 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_INT(int sig)
{
	(void)sig;
	if (gl.rl)
		return ;
	// waitpid(0, NULL, WNOHANG);
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler()
{
	// rl_catch_signals = 0;
	signal(SIGINT, handle_INT);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_lexer	*cmd;
	t_all	all;

	if (ac != 1 || av[1])
		return (printf("program does not accept agruments\n"), 0);
	set_env(&all, env);
	sig_handler();
	while (true)
	{
		gl.rl = 0;
		line = readline("sash>$ ");
		if (!line)
			return (printf("exit\n"), free_enex(all.env), free_enex(all.exp), gl.exit_status);
		if (*line)
			add_history(line);
		else
		{
			free(line);
			continue;
		}
		cmd = tokenize(line);
		if (!analyze_syntax(cmd))
			continue ;
		parse(&all, cmd);
		exec(&all);
		t_simple_cmd	*tmp;
		
		while (all.cmd)
		{
			// puts("aaaaaaa");
			tmp = all.cmd;
			all.cmd = all.cmd->next;
			if (tmp->str)
			{
				ft_freee(tmp->str);
			}
			free(tmp);
		}
	}
	free_enex(all.env);
	free_enex(all.exp);
	return 0;
}
