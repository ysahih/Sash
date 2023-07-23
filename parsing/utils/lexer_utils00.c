#include "../../minishell.h"

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
