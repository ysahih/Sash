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
	return (s);
}

char	*empty_str(char *s1, char *s2)
{
	if (s1 && s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	if (empty_str(s1, s2) != NULL)
		return (empty_str(s1, s2));
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

void	empty_quotes(t_lexer **cmdline, t_lexer **node)
{
	t_lexer	*cmd;

	cmd = *cmdline;
	if (!cmd->next)
		return ;
	if (cmd->type == DQUOTE && cmd->next->type == DQUOTE)
	{
		create_node(node, ft_strdup(""), -2, 0);
		cmd = cmd->next;
		cmd = cmd->next;
	}
	if (!cmd || !cmd->next)
		return ;
	
	if (cmd->type == SQUOTE && cmd->next->type == SQUOTE)
	{
		create_node(node, ft_strdup(""), -2, 0);
		cmd = cmd->next;
		cmd = cmd->next;
	}
	*cmdline = cmd;
}

t_lexer	*rm_quote(t_lexer *cmdline)
{
	t_lexer	*node;

	node = NULL;
	while (cmdline)
	{
		empty_quotes(&cmdline, &node);
		if (!cmdline)
			break ;
		if (cmdline->type != DQUOTE && cmdline->type != SQUOTE)
			create_node(&node, cmdline->str, cmdline->type, 0);
		cmdline = cmdline->next;
	}
	return (node);
}

void	join_words(t_lexer **node, t_lexer *cmd, char *str)
{
	while (cmd)
	{
		while (cmd && (cmd->type == WORD || cmd->type == -2))
		{
			str = ft_strjoin(str, cmd->str);
			cmd = cmd->next;
		}
		create_node(node, str, WORD, 0);
		str = NULL;
		if (!cmd)
			break ;
		else 
		{
			create_node(node, cmd->str, cmd->type, 0);
			cmd = cmd->next;
		}
	}
	if (cmd)
		create_node(node, cmd->str, cmd->type, 0);

}

t_lexer	*merge_word(t_lexer *cmd)
{
	t_lexer	*node;
	char 	*str;

	str = NULL;
	node = NULL;
	if (!cmd)
		return NULL;
	join_words(&node, cmd, str);
	return (node);
}

t_lexer	*rm_space(t_lexer *cmd)
{
	t_lexer	*node;

	node = NULL;
	while (cmd)
	{
		if (cmd->type != WSPACE)
			create_node(&node, cmd->str, cmd->type, 1);
		cmd = cmd->next;
	}
	free_gb();
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
}

int	count_wd(t_lexer *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd->type != PIPE)
	{
		if ((cmd->type == WORD && !cmd->previous) ||
			(cmd->type == WORD && cmd->previous && cmd->previous->type <= WORD))
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
	tmp->key = ft_strdup(s[0]);
	tmp->val = ft_strdup(s[1]);
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


	val = NULL;

	if (!strcmp("?", str))
		val = ft_itoa(gl.exit_status);
	while (var)
	{
		if (!strcmp(var->key, str))
		{
			val = var->val;
		}
		var = var->next;
	}
	return (val);
}

void	hd_var(t_lexer **node, t_lexer **cmdline)
{
	t_lexer *cmd;

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

t_lexer *expand_var(t_lexer *cmd, t_var *var)
{
	t_lexer *node;
	
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

void	read_hd( char *s, int fd[2])
{
	char	*line;

	while(true)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, s) == 0 || gl.rl)
		{
			gl.rl = 0;
			if (line)
				free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	free(s);
}

void	parse_hd(t_simple_cmd **scmd, t_lexer **cmdline)
{
	int		fd[2];
	char *s;

	if (pipe(fd) == -1)
	{
		(*scmd)->err = errno;
		return ;
	}
	rl_event_hook = event;
	signal(SIGINT, hd_sig);
	(*cmdline) = (*cmdline)->next;
	s = ft_strdup("");
	if ((*cmdline))
	{
		free(s);
		s = (*cmdline)->str;
	}
	read_hd( s, fd);
	if ((*cmdline))
		(*cmdline) = (*cmdline)->next;
	(*scmd)->in_fd = fd[0];
}

void	set_out_fd(t_simple_cmd **cmd, int new_fd)
{
	int	old_fd;

	old_fd = (*cmd)->out_fd;
	if (old_fd != 1)
		close(old_fd);
	(*cmd)->out_fd = new_fd;
		if((*cmd)->out_fd < 0)
			(*cmd)->err = errno;
}

void	set_in_fd(t_simple_cmd **cmd, int new_fd)
{
	int	old_fd;

	old_fd = (*cmd)->in_fd;
	if (old_fd != 0)
		close(old_fd);
	(*cmd)->in_fd = new_fd;
		if((*cmd)->in_fd < 0)
			(*cmd)->err = errno;
}

void	parse_red(t_lexer **cmdline, t_simple_cmd **cmd)
{
	int		flag;
	int		new_fd;

	flag = (*cmdline)->type;
	(*cmdline) = (*cmdline)->next;
	if (flag == OUTRED)
	{
		new_fd = open((*cmdline)->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		set_out_fd(cmd, new_fd);
	}
	else if (flag == INRED)
	{
		new_fd = open((*cmdline)->str, O_RDONLY, 0644);
		set_in_fd(cmd, new_fd);
	}
	else if (flag == APPEND)
	{
		new_fd = open((*cmdline)->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		set_out_fd(cmd, new_fd);
	}
	free((*cmdline)->str);
	(*cmdline) = (*cmdline)->next;
}

void	collect_filenames(t_lexer **node)
{
	struct dirent	*entry;
	DIR 			*dir;

	dir = NULL;
	dir = opendir(".");
	if (dir == NULL)
		perror("opendir");
	
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			create_node(node, entry->d_name, WORD, 0);
			create_node(node, " ", WSPACE, 0);
		}
	}
}

t_lexer	*parse_wc(t_lexer *cmd)
{
	t_lexer 		*node;

	node = NULL;
	while (cmd)
	{
		if (cmd->type == -1)
			collect_filenames(&node);
		else
			create_node(&node, cmd->str, cmd->type, 0);
		cmd = cmd->next;
	}
	return (node);
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
		else if((*cmdline)->type == HERDOC)
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
	t_lexer *cmd;

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
	t_simple_cmd 	*scmd;
	t_lexer 		*cmd;
	t_lexer			*tmp1;
	t_lexer			*tmp2;

	scmd = NULL;
	cmd = filter(all, cmdline);
	tmp1 = cmd;
	while(cmd)
		add_scmd(&scmd, collect_scmds(&cmd, 0));
	while (tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1);
		tmp1 = tmp2;
	}
	all->cmd = scmd;
}