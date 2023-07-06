#include "minishell.h"

char	*ft_strncpy(char *s, char *s2, int len)
{
	int	i;

	i = 0;
	while (i < len && s2[i])
	{
		s[i] = s2[i];
		i++;
	}
	s[len] = '\0';
	return (s);
}

int	count_len(char *str)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == '=')
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != '=')
			i++;
	}
	return (++count);
}

char	**ft_split(char *str)
{
	char	**s;
	int		i;
	int		j;
	int		a;

	s = malloc((sizeof(char *)) * (count_len(str)));
	if (!s)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == '=')
			i++;
		a = i;
		while (str[i] && str[i] != '=')
			i++;
		if (i > a)
			s[j++] = ft_strncpy(malloc (i - a + 1), str + a, i - a);
	}
	s[j] = NULL;
	// printf("%s=%s\n", s[0], s[1]);
	return (s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	if(!s1)
		return (s2);
	if(!s2)
		return (s1);
	p = (char *)malloc (ft_strlen (s1) + ft_strlen (s2) + 1);
	if (!p)
		return (0);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
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
	// t_lexer	*tmp;
	char 	*str;

	str = NULL;
	node = NULL;
	if (!cmd)
		return NULL;
	while (cmd)
	{
		while (cmd && cmd->type == WORD)
		{
			str = ft_strjoin(str, cmd->str);
			cmd = cmd->next;
		}
		create_node(&node, str, WORD);
		str = NULL;
		if (!cmd)
			break ;
		else 
		// if (cmd->type != WORD)
		{
			create_node(&node, cmd->str, cmd->type);
			cmd = cmd->next;
		}
	}
	if (cmd)
		create_node(&node, cmd->str, cmd->type);
	// while (cmd)
	// {
	// 	tmp = cmd->next;
	// 	free(cmd);
	// 	cmd = tmp;
	// }
	return (node);
}

t_lexer	*rm_space(t_lexer *cmd)
{
	t_lexer	*node;
	t_lexer	*tmp;

	node = NULL;
	while (cmd)
	{
		if (cmd->type != WSPACE)
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

t_var	*last_var(t_var *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_simple_cmd	*last_cmd(t_simple_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_scmd(t_simple_cmd **lst, t_simple_cmd *new)
{
	t_simple_cmd	*last_node;
	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = last_cmd(*lst);
	last_node->next = new;
    last_node->next->previous = last_node;
}

int	count_wd(t_lexer *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if ((cmd->type == WORD && !cmd->previous) || (cmd->type == WORD && cmd->previous && cmd->previous->type <= WORD))
			i++;
		cmd = cmd->next;
	}
	return (i);
}

t_simple_cmd *create_scmd(t_lexer *cmd)
{
	t_simple_cmd 	*scmd;
	int				i;

	i = count_wd(cmd) + 1;
	scmd = malloc(sizeof(t_simple_cmd));
	scmd->str = malloc(sizeof(char *) * i);
	scmd->next = NULL;
	scmd->previous = NULL;
	scmd->in_fd = 0;
	scmd->out_fd = 1;
	scmd->err = 0;
	return (scmd);
}

void	lst_var(t_var **var, char **s)
{
	t_var	*tmp;
	t_var	*last;

	if (!var || !s || !*s)
		return ;
	tmp = malloc(sizeof(t_var));
	tmp->key = s[0];
	tmp->val = s[1];
	tmp->next = NULL;
	if (*var == NULL)
	{
		*var = tmp;
		return ;
	}
	last = last_var(*var);
	last->next = tmp;
}

char	*find_var(t_var *var, char *str)
{
	char	*val;
	// bool	flag;

	val = NULL;
	// flag = false;
	while (var)
	{
		if (!strcmp(var->key, str))
		{
			val = var->val;
			// flag = true;
		}
		var = var->next;
	}
	// if (!flag)
	// 	return NULL;
	return (val);
}

t_lexer *expand_var(t_lexer *cmdline, t_var *var)
{
	t_lexer *node;
	t_lexer	*cmd;

	cmd = cmdline;
	
	node = NULL;
	while (cmd)
	{
		if (cmd->type == VAR)
			create_node(&node, find_var(var, cmd->str), WORD);
		else
			create_node(&node, cmd->str, cmd->type);
		cmd = cmd->next;
	}

	return (node);
}

// int	event(void)
// {
// 	return (0);
// }

// void	hd_sig(int sig)
// {
// 	(void)sig;
// 	g_rd = 1;
// 	rl_done = 1;
// }

void	parse_hd(t_simple_cmd **scmd, t_lexer **cmdline)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		(*scmd)->err = errno;
	}
	// rl_event_hook = event;
	// signal(SIGINT, hd_sig);
	while(true)
	{
		line = readline("> ");
		if (!line || strcmp(line, (*cmdline)->str) == 0 || g_rd)
		{
			g_rd = 0;
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
	(*scmd)->in_fd = fd[0];
}

t_simple_cmd	*collect_scmds(t_lexer **cmdline)
{

	t_simple_cmd	*cmd;
	int				i;

	i = 0;

	cmd = create_scmd(*cmdline);
	while (*cmdline)
	{
		if ((*cmdline)->type == PIPE)
		{
			*cmdline = (*cmdline)->next;
			break ;
		}
		else if ((*cmdline)->type < 0)
		{
			(*cmdline) = (*cmdline)->next;
		}
		else if ((*cmdline)->type == OUTRED)
		{
			(*cmdline) = (*cmdline)->next;
			cmd->out_fd = open((*cmdline)->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if(cmd->out_fd < 0)
				cmd->err = errno;
			(*cmdline) = (*cmdline)->next;
		}
		else if ((*cmdline)->type == INRED)
		{
			(*cmdline) = (*cmdline)->next;
			cmd->in_fd = open((*cmdline)->str, O_RDONLY, 0644);
			if(cmd->in_fd < 0)
				cmd->err = errno;
			(*cmdline) = (*cmdline)->next;
		}
		else if ((*cmdline)->type == APPEND)
		{
			(*cmdline) = (*cmdline)->next;
			cmd->out_fd = open((*cmdline)->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if(cmd->out_fd < 0)
				cmd->err = errno;
			(*cmdline) = (*cmdline)->next;
		}
		// else if((*cmdline)->type == HERDOC)
		// {
		// 	(*cmdline) = (*cmdline)->next;
		// 	parse_hd(&cmd, cmdline);
		// 	(*cmdline) = (*cmdline)->next;
		// }
		else if ((*cmdline)->type == WORD)
		{
			cmd->str[i] = (*cmdline)->str;
			i++;
			(*cmdline) = (*cmdline)->next;
		}
	}
	cmd->str[i] = NULL;
	return (cmd);
}


void	parse(t_all *all, t_lexer *cmdline)
{
	t_simple_cmd 	*scmd;
	t_lexer 		*cmd;

	scmd = NULL;

	cmd = rm_quote(cmdline);
	cmd = expand_var(cmd, all->env);
	cmd = merge_word(cmd);
	cmd = rm_space(cmd);

	while(cmd)
		add_scmd(&scmd, collect_scmds(&cmd));


	all->cmd = scmd;

	// while (scmd)
	// {
	// 	i = 0;
	// 	printf("--\n");
	// 	while (scmd->str[i]){  
	// 	printf("=%s=\n", scmd->str[i]);
	// 		i++;
	// 	}
	// 	printf("--\n");
	// 	scmd = scmd->next;
	// }
}