#include "minishell.h"



void	handle_INT(int sig)
{
	(void)sig;
	if (gl.rl)
		return ;
	// waitpid(0, NULL, WNOHANG);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler()
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_INT);
	signal(SIGQUIT, SIG_IGN);
}

char	**ft_free(char **p, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

char	**ft_freee(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

void	set_env(t_all *all, char **env)
{
	// t_var	*oldpwd;
	int		i;
	char	path[800];
	char	**str;

	i = 0;
	gl.gc = NULL;
	all->env = NULL;
	all->exp = NULL;
	if (!*env)
	{
		add_exen_back(&all->exp ,lstnew_exen(ft_strdup("OLDPWD"), NULL));
		add_exen_back(&all->exp ,lstnew_exen(ft_strdup("PWD"), ft_strdup(getcwd(path, 800))));
		add_exen_back(&all->exp ,lstnew_exen(ft_strdup("SHLVL"), ft_strdup("1")));
		add_exen_back(&all->env ,lstnew_exen(ft_strdup("PWD"), ft_strdup(getcwd(path, 800))));
		add_exen_back(&all->env ,lstnew_exen(ft_strdup("SHLVL"), ft_strdup("1")));
		add_exen_back(&all->env ,lstnew_exen(ft_strdup("_"), ft_strdup("/usr/bin/env")));
		return ;
	}
	while (env[i])
	{
		str = ft_split(env[i]);
		lst_var(&all->env, str);
		lst_var(&all->exp, str);
		ft_freee(str);
		i++;
	}
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
		line = readline("sash$ ");
		// ft_putstr_fd(line, 2);
		if (!line)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*line)
			add_history(line);
		else
		{
			free(line);
			continue;
		}
		cmd = tokenize(line);
		// free(line);
		if (!analyze_syntax(cmd))
		{
			// printf("%d\n", gl.exit_status);
			continue ;
		}
		parse(&all, cmd);
		exec(&all);

		// t_simple_cmd	*tmp;
		// int		i = 0;
		// tmp = all.cmd;
		// while (tmp)
		// {
		// 	i++;
		// 	tmp = tmp->next;
		// }
		// while (all.cmd)
		// {
		// 	// puts("aaaaaaa");
		// 	tmp = all.cmd;
		// 	all.cmd = all.cmd->next;
		// 	if (tmp->str)
		// 	{
		// 		ft_freee(tmp->str);
		// 	}
		// 	free(tmp);
		// }
		// system("leaks sash");
	}
	return 0;
}
