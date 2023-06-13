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

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;
	

	i = 0;
	j = 0;
	if (!dest && !src)
		return (NULL);
	if(!dest)
		return (src);
	if(!src)
		return (dest);
	while (dest[j] != '\0')
		j++;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	// printf("%s\n", dest);
	return (dest);
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
	t_lexer	*tmp;

	node = NULL;
	if (!cmd)
		return NULL;
	while (cmd)
	{
		if (cmd->next && cmd->type == WORD && cmd->next->type == WORD)
		{
			create_node(&node, ft_strcat(cmd->str, cmd->next->str) , WORD);
			cmd = cmd->next->next;
		}
		if (!cmd)
			break ;
		else
		{
			create_node(&node, cmd->str, cmd->type);
			cmd = cmd->next;
		}
	}
	if (cmd)
		create_node(&node, cmd->str, cmd->type);
	while (cmd)
	{
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
	return (node);
}

t_lexer	*rm_space(t_lexer *cmd)
{
	t_lexer	*node;
	t_lexer	*tmp;

	node = NULL;
	while (cmd)
	{
		if (cmd->type != SPACE)
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

void	add_cmd(t_simple_cmd **lst, t_simple_cmd *new)
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

t_simple_cmd *create_scmd(void)
{
	t_simple_cmd 	*scmd;

	scmd = malloc(sizeof(t_simple_cmd));
	scmd->str = malloc(sizeof(char *));
	scmd->next = NULL;
	scmd->previous = NULL;
	scmd->in_fd = 0;
	scmd->out_fd = 1;
	return (scmd);
}

void	collect_cmds(t_simple_cmd **node, t_lexer **cmd)
{
	t_simple_cmd 	*scmd;
	int				i;

	i = 0;
	if (!cmd || !node)
		return ;
	scmd = create_scmd();
	while((*cmd) && (*cmd)->type != PIPE)
	{
		while ((*cmd) && (*cmd)->type >= OUTRED)
		{
			if ((*cmd)->type == OUTRED)
			{
				scmd->out_fd = open((*cmd)->next->str, O_CREAT | O_TRUNC, 0644);
			}
			if ((*cmd)->type == INRED)
				scmd->in_fd = open((*cmd)->next->str, O_WRONLY, 0644);
			if ((*cmd)->type == APPEND)
				scmd->out_fd = open((*cmd)->next->str, O_CREAT | O_APPEND, 0644);
			perror("sash: ");//errno
			// if ((*cmd)->type == HERDOC)
				// scmd->in_fd = ;
			(*cmd) = (*cmd)->next->next;

		}
		if (!(*cmd) || (*cmd)->type == PIPE)
			break ;
		
		scmd->str[i++] = (*cmd)->str;
		(*cmd) = (*cmd)->next;
	}
	add_cmd(node, scmd);
	// i= 0;
	// t_simple_cmd *tmp = *node;
	// // while ((tmp))
	// // {
		// while(tmp->str[i] != NULL)
		// {

		// 	printf("%s-\n", tmp->str[i++]);
		// }
		// tmp = tmp->next;
	// }
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
	bool	flag;

	flag = false;
	while (var)
	{
		if (!strcmp(var->key, str))
		{
			val = var->val;
			flag = true;
		}
		var = var->next;
	}
	if (!flag)
		return NULL;
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
		if (cmd->type == VAR){
		
			create_node(&node, find_var(var, cmd->str), WORD);
		}
		else{
			create_node(&node, cmd->str, cmd->type);

		}
		cmd = cmd->next;
	}

	return (node);
}

void	parse(t_lexer *cmdline, char **env)
{
	t_simple_cmd 	*scmd;
	t_lexer 		*cmd;
	t_var			*var;

	scmd = NULL;
	int i = 0;
	var = NULL;
	while (env[i])
	{
		lst_var(&var, ft_split(env[i]));
		i++;
	}
	cmd = rm_quote(cmdline);

	cmd = expand_var(cmd, var);

	cmd = merge_word(cmd);
	cmd = rm_space(cmd);

	while (cmd)
	{
		if (cmd->type == PIPE)
			cmd = cmd->next;
		if (cmd)
			collect_cmds(&scmd, &cmd);
		else if (cmd == NULL)
			break ;
	}
	// puts("he");
	// printf("{%s}", cmd->str);
	// i =0;
	// t_simple_cmd *tmp = scmd;
	// while ((tmp))
	// {
		// while(tmp->str[i] != NULL)
	// 		printf("%s-\n", tmp->str[i++]);
		// tmp = tmp->next;
	// }
}