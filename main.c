#include "minishell.h"

t_global	gl;

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

	// p = all->cmd;
	i = 0;
	// gl.gc = NULL;
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

void	free_enex(t_var *lst)
{
	t_var		*p;
	t_var		*p1;

	p = lst;
	while (p)
	{
		p1 = p->next;
		free(p->key);
		p->key = NULL;
		free(p->val);
		p->val = NULL;
		free (p);
		p = NULL;
		p = p1;
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
		line = readline("sash>$ ");
		if (!line)
			return (printf("exit\n"), gl.exit_status);
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
		// system("leaks sash");
		// t_simple_cmd	*tmp;
		
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
	}
	// free_enex(all.env);
	// free_enex(all.exp);
	return 0;
}
