/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:18:12 by ysahih            #+#    #+#             */
/*   Updated: 2023/07/23 17:18:13 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	tokenize_word(t_lexer **node, char **s)
{
	char	*tmp;
	int		i;

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
	while (tmp[i] && valid_var(tmp[i]))
		i++;
	create_node(node, ft_strcpy(tmp, i), VAR, 0);
	*s += i;
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

void	tokenize_red(t_lexer **node, char **s)
{
	char	*line;

	line = *s;
	if (*line == '>')
		out_red(node, &line);
	else if (*line == '<')
		in_red(node, &line);
	*s = line;
}
