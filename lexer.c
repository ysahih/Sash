#include "minishell.h"

void	tokenize_word(t_lexer **node, char **s)
{
	char *tmp;
	int	i;

	i = 0;
	tmp = *s;
	while (tmp[i] && !is_symbol(tmp[i]))
	{
		if (tmp[i] == '$' && tmp[i + 1] && valid_var(tmp[i + 1]))
			break ;
		i++;
	}
	create_node(node, ft_strcpy(*s, i), WORD, 0);
	*s += i;
}

void	tokenize_var(t_lexer **node, char **s)
{
	int		i;
	char	*tmp;

	i = 0;
	*s += 1;
	tmp = *s;
	if (tmp[0] == '?')
	{
		create_node(node, "?", VAR, 0);
		*s += 1;
		return ;
	}
	if (!tmp[i] || !valid_var(tmp[i]))
		return ;
	while(tmp[i] && valid_var(tmp[i]))
		i++;
	create_node(node, ft_strcpy(tmp, i), VAR, 0);
	*s += i;
}

void	quote_word(t_lexer **node, char *s, int *i, int j)
{
	char *tmp;

	tmp = s;
	j = *i;
	while (tmp[*i] && tmp[*i] != '"')
	{
		if (tmp[*i] == '$' && tmp[*i + 1] && valid_var(tmp[*i + 1]))
			break ;
		(*i)++;
	}
	create_node(node, ft_strcpy(s + j, *i - j), WORD, 0);
}

char *set_quote(t_lexer **node, char **s)
{
	char *tmp;

	*s += 1;
	tmp = *s;
	create_node(node, "\"", DQUOTE, 0);
	return (tmp);
}

void	close_quotes(t_lexer **node, char **s, char *tmp, int i)
{
	create_node(node, "\"", DQUOTE, 0);
	*s = &tmp[++i];
	return ;
}

void	tokenize_dquote(t_lexer **node, char **s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = set_quote(node, s);
	while (tmp[i])
	{
		if (tmp[i] == '"')
			return (close_quotes(node, s, tmp, i));
		if (tmp[i] == '$' && tmp[i + 1] && valid_var(tmp[i + 1]))
		{
			j = ++i;
			while (tmp[i] && valid_var(tmp[i]))
				i++;
			create_node(node, ft_strcpy(tmp + j, i - j), VAR, 0);
			*s = &tmp[i];
		}
		else
		{
			quote_word(node, tmp, &i, j);
			*s += i;
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
	create_node(node, "'", SQUOTE, 0);
	while (tmp[i] && tmp[i] != '\'')
		i++;
	if (i)
		create_node(node, ft_strcpy(tmp, i), WORD, 0);
	if (tmp[i] == '\'')
	{
		create_node(node, "'", SQUOTE, 0);
		i++;
	}
	*s += i;
}

void	in_red(t_lexer **node, char **line)
{
	char	*str;

	str = *line;
	if (*(str + 1) && *(str + 1) == '<')
	{
		create_node(node, "<<", HERDOC, 0);
		str++;
	}
	else
		create_node(node, "<", INRED, 0);
	str++;
	*line = str;
}

void	out_red(t_lexer **node, char **line)
{
	char	*str;

	str = *line;
	if (*(str + 1) && *(str + 1) == '>')
	{
		create_node(node, ">>", APPEND, 0);
		str++;
	}
	else
		create_node(node, ">", OUTRED, 0);
	str++;
	*line = str;
}

void	tokenize_red(t_lexer **node, char **s)
{
	char *line;

	line = *s;
	if (*line == '>')
		out_red(node, &line);
	else if (*line == '<')
		in_red(node, &line);
	*s = line;
}

void	get_token(t_lexer **node, char **line)
{
	if (**line == '|')
	{
		create_node(node, "|", PIPE, 0);
		(*line)++;
	}
	if (**line == ' ')
	{
		create_node(node, " ", WSPACE, 0);
		while (is_ws(**line))
			(*line)++;
	}
	if (**line == '*')
	{
		create_node(node, "*", -1, 0);
		(*line)++;
	}
}

char *set_line(t_lexer **node, char **line)
{
	char *tmp;

	tmp = *line;
	*node = NULL;
	while (is_ws(**line))
		(*line)++;
	return (tmp);
}

t_lexer	*tokenize(char *line)
{
	t_lexer *node;
	char 	*tmp;

	tmp = set_line(&node, &line);
	while (*line)
	{
		if (*line == ' ' || *line == '*' || *line == '|')
			get_token(&node, &line);
		else if (*line == '"')
			tokenize_dquote(&node, &line);
		else if (*line == '\'')
			tokenize_squote(&node, &line);
		else if (*line == '>'|| *line == '<')
			tokenize_red(&node, &line);
		else if (*line == '$' && *(line + 1) &&
			(valid_var(*(line + 1)) || *(line + 1) == '?'))
			tokenize_var(&node, &line);
		else
			tokenize_word(&node, &line);
	}
	free(tmp);
	return (node);
}