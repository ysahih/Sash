#include "minishell.h"

void	tokenize_word(t_lexer **node, char **s)
{
	int	i;

	char *tmp;

	tmp = *s;
	i = 0;
	
	while (tmp[i] && !is_symbol(tmp[i]))
	{
		if (tmp[i] == '$' && tmp[i + 1] && valid_var(tmp[i + 1]))
			break ;
		i++;
	}
	create_node(node, ft_strcpy(*s, i), WORD);
	*s += i;
}

void	tokenize_var(t_lexer **node, char **s)
{
	int		i;
	char	*tmp;

	i = 0;
	*s += 1;
	tmp = *s;
	if (!tmp[i] || !valid_var(tmp[i]))
		return ;
	while(tmp[i] && valid_var(tmp[i]))
		i++;
	create_node(node, ft_strcpy(tmp, i), VAR);
	*s += i;
}

void	tokenize_dquote(t_lexer **node, char **s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	*s += 1;
	tmp = *s;
	create_node(node, "\"", DQUOTE);
	while (tmp[i])
	{
		if (tmp[i] == '"')
		{
			create_node(node, "\"", DQUOTE);
			*s = &tmp[++i];
			return ;
		}
		if (tmp[i] == '$' && tmp[i + 1] && valid_var(tmp[i + 1]))
		{
			j = ++i;
			while (tmp[i] && valid_var(tmp[i]))
				i++;
			create_node(node, ft_strcpy(tmp + j, i - j), VAR);
			*s = &tmp[i];
		}
		else
		{
			j = i;
			while (tmp[i] && tmp[i] != '"')
			{
				if (tmp[i] == '$' && tmp[i + 1] && valid_var(tmp[i + 1]))
					break ;
				i++;
			}
			create_node(node, ft_strcpy(tmp + j, i - j), WORD);
			*s = &tmp[i];
		}
	}
}

void	tokenize_squote(t_lexer **node, char **s)
{
	char	*tmp;
	int		i;

	i = 0;
	*s += 1;
	tmp = *s;
	create_node(node, "'", SQUOTE);
	while (tmp[i] && tmp[i] != '\'')
		i++;
	if (i)
		create_node(node, ft_strcpy(tmp, i), WORD);
	if (tmp[i] == '\'')
	{
		create_node(node, "'", SQUOTE);
		i++;
	}
	// printf("|%c|\n", tmp[i - 1]);
	*s += i;
}

void	tokenize_red(t_lexer **node, char **s)
{
	char *line;

	line = *s;
	if (*line == '>')
	{
		if (*(line + 1) && *(line + 1) == '>')
		{
			create_node(node, ">>", APPEND);
			line++;
		}
		else
			create_node(node, ">", OUTRED);
		line++;
	}
	else if (*line == '<')
	{
		if (*(line + 1) && *(line + 1) == '<')
		{
			create_node(node, "<<", HERDOC);
			line++;
		}
		else
			create_node(node, "<", INRED);
		line++;
	}
	*s = line;
}

t_lexer	*tokenize(char *line)
{
	t_lexer *node;

	node = NULL;
	while(*line == ' ') 
		line++;
	while (*line)
	{
		if (*line == ' ')
		{
			create_node(&node, " ", SPACE);
			while (*line == ' ')
				line++;
		}
		else if (*line == '|')
		{
			create_node(&node, "|", PIPE);
			line++;
		}
		else if (*line == '"')
			tokenize_dquote(&node, &line);
		else if (*line == '\'')
			tokenize_squote(&node, &line);
		else if (*line == '>'|| *line == '<')
			tokenize_red(&node, &line);
		else if (*line == '$' && *(line + 1) && valid_var(*(line + 1)))
			tokenize_var(&node, &line);
		else
			tokenize_word(&node, &line);
	}
	// t_lexer	 *tmp = node;
	// puts("ls");
	// while (tmp)
	// {
	// 	printf("----|%s|---%d--\n", tmp->str, tmp->type);
	// 	tmp = tmp->next;
	// }
	return (node);
}