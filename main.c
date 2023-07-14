#include "minishell.h"



void	handle_INT(int sig)
{
	(void)sig;

	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
// 	// else
// 	// {
// 		// g_interrupte = 1;
// 		// rl_catch_signals = 0;
// 		// printf("\n");
// 		// rl_on_new_line();
// 		// rl_replace_line("", 0);
// 		// rl_redisplay();
// 		// return ;
// 	// }
	
// }

// void	handle_QUIT()
// {
	
// }
void	sig_handler()
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_INT);
	signal(SIGQUIT, SIG_IGN);
}

void	set_env(t_all *all, char **env)
{
	t_var	*oldpwd;
	int		i;
	char	path[800];

	i = 0;
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
		lst_var(&all->env, ft_split(env[i]));
		lst_var(&all->exp, ft_split(env[i]));
		i++;
	}
	// all->env = unset_env("OLDPWD", &all->env);
	// oldpwd = check_char(all->exp, "OLDPWD");
	// free(oldpwd->val);
	// oldpwd->val = NULL;
}



int	main(int ac, char **av, char **env)
{
	char	*line;
	t_lexer	*cmd;
	t_simple_cmd	*cp;
	t_all	all;
	pid_t fg_pid; 
	int status;

	// g_rd = 0;
	if (ac != 1 || av[1])
		return (printf("program does not accept agruments"), 0);

	set_env(&all, env);
	// printf("%d", getpid());
	while (true)
	{
	
		waitpid(fg_pid, &status, 0);
		sig_handler();
		line = readline("sash$ ");
		if (!line)
			break;
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
		cp = all.cmd;
		while (cp)
		{
			int i = 0;
			printf("in : %d\nout : %d\nerr : %d\n", cp->in_fd, cp->out_fd, cp->err);
			while (cp->str[i])
			{
				printf("%s\n", cp->str[i]);
				i++;
			}
			cp = cp->next;
		}
		exec(&all);
	}
}
