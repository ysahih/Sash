#include "minishell.h"

// void	builtin_cmds(char *s)
// {
// 	if (!strcmp(s, "exit"))
// 		exit(0); 
// }

// bool	is_digit(char c)
// {
// 	return (c >= '0' && c <= '9');
// }

// bool	is_symbol(char c)
// {
// 	return (c == ' ' || c == '\'' || c == '"' || c == '|'
// 		|| c == '<' || c == '>'|| c == '*');
// }

// int	ft_strlen(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (i[s])
// 		i++;
// 	return (i);
// }

// // bool	special_char(int c)
// // {
// // 	return (c == '0' && c == '_' && c == '?' && c == ' ' && c == '"');
// // }


// bool	is_alnum(char c)
// {
// 	return ((c >= 'a' && c <= 'z')
// 		|| (c >= 'A' && c <= 'Z') || is_digit(c));
// }

// bool	is_alpha(int c)
// {
// 	return ((c >= 'a' && c <= 'z')
// 		|| (c >= 'A' && c <= 'Z'));
// }

// bool	valid_var(char c)
// {
// 	return (is_alpha(c) || is_digit(c) || c == '_');
// }

// char	*ft_strcpy(char *str, int size)
// {
// 	int	i;
// 	char *word;

// 	i = 0; 
// 	word = malloc(size + 1);
// 	while (str[i] && i < size)
// 	{
// 		word[i] = str[i];
// 		i++;
// 	}
// 	word[i] = '\0';
// 	return (word);
// }


// void	tokenize_word(t_lexer **node, char **s)
// {
// 	int	i;

// 	char *tmp;

// 	tmp = *s;
// 	i = 0;
	
// 	while (tmp[i] && !is_symbol(tmp[i]))
// 	{
// 		if (tmp[i] == '$' && tmp[i + 1] && valid_var(tmp[i + 1]))
// 			break ;
// 		i++;
// 	}
// 	create_node(node, ft_strcpy(*s, i), WORD);
// 	*s += i;
// }

// void	tokenize_var(t_lexer **node, char **s)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;

// 	i = 0;
// 	*s += 1;
// 	tmp = *s;
// 	if (!tmp[i] || !valid_var(tmp[i]))
// 		return ;
// 	while(tmp[i] && valid_var(tmp[i]))
// 		i++;
// 	create_node(node, ft_strcpy(tmp, i), VAR);
// 	*s += i;
// }

// void	tokenize_dquote(t_lexer **node, char **s)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;

// 	i = 0;
// 	*s += 1;
// 	tmp = *s;
// 	create_node(node, "\"", DQUOTE);
// 	while (tmp[i])
// 	{
// 		if (tmp[i] == '"')
// 		{
// 			create_node(node, "\"", DQUOTE);
// 			*s = &tmp[++i];
// 			return ;
// 		}
// 		if (tmp[i] == '$' && tmp[i + 1] && valid_var(tmp[i + 1]))
// 		{
// 			j = ++i;
// 			while (tmp[i] && valid_var(tmp[i]))
// 				i++;
// 			create_node(node, ft_strcpy(tmp + j, i - j), VAR);
// 			*s = &tmp[i];
// 		}
// 		else
// 		{
// 			j = i;
// 			while (tmp[i] && tmp[i] != '"')
// 			{
// 				if (tmp[i] == '$' && tmp[i + 1] && valid_var(tmp[i + 1]))
// 					break ;
// 				i++;
// 			}
// 			create_node(node, ft_strcpy(tmp + j, i - j), WORD);
// 			*s = &tmp[i];
// 		}
// 	}
// }

// void	tokenize_squote(t_lexer **node, char **s)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	*s += 1;
// 	tmp = *s;
// 	create_node(node, "'", SQUOTE);
// 	while (tmp[i] && tmp[i] != '\'')
// 		i++;
// 	if (i)
// 		create_node(node, ft_strcpy(tmp, i), WORD);
// 	if (tmp[i] == '\'')
// 	{
// 		create_node(node, "'", SQUOTE);
// 		i++;
// 	}
// 	// printf("|%c|\n", tmp[i - 1]);
// 	*s += i;
// }

// void	tokenize_red(t_lexer **node, char **s)
// {
// 	char *line;

// 	line = *s;
// 	if (*line == '>')
// 	{
// 		if (*(line + 1) && *(line + 1) == '>')
// 		{
// 			create_node(node, ">>", APPEND);
// 			line++;
// 		}
// 		else
// 			create_node(node, ">", OUTRED);
// 		line++;
// 	}
// 	else if (*line == '<')
// 	{
// 		if (*(line + 1) && *(line + 1) == '<')
// 		{
// 			create_node(node, "<<", HERDOC);
// 			line++;
// 		}
// 		else
// 			create_node(node, "<", INRED);
// 		line++;
// 	}
// 	*s = line;
// }


// t_lexer	*tokenize(char *line)
// {
// 	t_lexer *node;

// 	node = NULL;
// 	while(*line == ' ') 
// 		line++;
// 	while (*line)
// 	{
// 		if (*line == ' ')
// 		{
// 			create_node(&node, " ", SPACE);
// 			while (*line == ' ')
// 				line++;
// 		}
// 		else if (*line == '|')
// 		{
// 			create_node(&node, "|", PIPE);
// 			line++;
// 		}
// 		else if (*line == '"')
// 			tokenize_dquote(&node, &line);
// 		else if (*line == '\'')
// 			tokenize_squote(&node, &line);
// 		else if (*line == '>'|| *line == '<')
// 			tokenize_red(&node, &line);
// 		else if (*line == '$' && *(line + 1) && valid_var(*(line + 1)))
// 			tokenize_var(&node, &line);
// 		else
// 			tokenize_word(&node, &line);
// 	}
// 	t_lexer	 *tmp = node;
// 	while (tmp)
// 	{
// 		printf("----|%s|---%d--\n", tmp->str, tmp->type);
// 		tmp = tmp->next;
// 	}
// 	return (node);
// }
// bool	pipe_checker(t_lexer *cmd, int i)
// {
// 	if (i && cmd->type == SPACE && cmd->next == NULL)
// 		return false;
// 	if (!i && cmd->type == SPACE && cmd->previous == NULL)
// 		return false;
// 	else if (cmd->next && cmd->previous)
// 	{
// 		if (i && cmd->type == SPACE && cmd->next)
// 			cmd = cmd->next;
// 		else if (!i && cmd->type == SPACE && cmd->previous)
// 			cmd = cmd->previous;
// 	}
// 	if (i)
// 		return (cmd->type >= VAR && cmd->type <= HERDOC);
// 	return (cmd->type >= VAR && cmd->type <= DQUOTE);
// }

// bool	pipe_analyze(t_lexer *cmd)
// {
// 	bool	flag;

// 	flag = true;
// 	if (cmd->next == NULL || cmd->previous == NULL)
// 		flag = false;
// 	else if (cmd->next && cmd->previous)
// 	{
// 		flag *= pipe_checker(cmd->next, 1);
// 		flag *= pipe_checker(cmd->previous, 0);
// 	}
// 	// printf("%d\n", flag);

// 	if (!flag){
// 		write (1, "error\n", 6);
// 		return false;
// 	}
// 	return true;
// }

// bool analyze_quote(t_lexer **node, int flag)
// {
// 	t_lexer	*cmd;

// 	cmd = *node;
// 	if (!cmd->next)
// 		return false ;
// 	cmd = cmd->next;
// 	while(cmd && cmd->type != flag)
// 		cmd = cmd->next;

// 	*node = cmd;
// 	if (!cmd)
// 		return false ;
// 	return true;
// }

// bool	analyze_syntax(t_lexer *cmd)
// {
// 	bool flag;

// 	flag = true;
// 	while (cmd)
// 	{
// 		if (cmd->type == SPACE && cmd->next)
// 			cmd = cmd->next;
// 		if (cmd->type == PIPE)
// 		{
// 			flag *= pipe_analyze(cmd);
// 			if (!flag)
// 				return false;
// 		}
// 		if (cmd->type >= OUTRED && cmd->type <=  HERDOC)
// 		{
// 			if (cmd->next)
// 			{
// 				if (cmd->next->type == SPACE)
// 					cmd = cmd->next;
// 			}
// 			if (!cmd->next || (cmd->next->type <= WORD && cmd->next->type >= DQUOTE))
// 			{
// 				return false;
// 			}
// 		}
// 		if (cmd->type == SQUOTE || cmd->type == DQUOTE )
// 		{
// 			if (cmd->type == SQUOTE)
// 			{
// 				flag *= analyze_quote(&cmd, SQUOTE);
// 				if (!flag)
// 					return false;
// 			}
// 			if (cmd->type == DQUOTE)
// 			{
// 				flag *= analyze_quote(&cmd, DQUOTE);
// 				if (!flag)
// 					return false;
// 			}
// 		}
// 		cmd = cmd->next;
// 	}
// 	return true;
// }

void	handle_INT(int sig)
{
	(void)sig;
	rl_catch_signals = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_QUIT()
{
	
}
void	sig_handler(void)
{
	signal(SIGINT, handle_INT);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	// char	**cpy;
	t_lexer	*cmd;
	t_all	all;

	// cpy = env;
	if (ac != 1 || av[1])
		return (printf("program does not accept agruments"), 0);
	while (true)
	{
		sig_handler();
		rl_catch_signals = 0;
		line = readline("sash$ ");
		// printf("%s\n", line);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		cmd = tokenize(line);
		if (!analyze_syntax(cmd))
		{
			write (1, "syntax error\n", 13);
			continue ;
		}
		parse(&all, cmd, env);
		if (*line)
			add_history(line);
		exec(&all);
	}
}
