/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:18:25 by ysahih            #+#    #+#             */
/*   Updated: 2023/07/23 17:18:26 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*tokenize(char *line)
{
	t_lexer	*node;
	char	*tmp;

	tmp = set_line(&node, &line);
	while (*line)
	{
		if (*line == ' ' || *line == '*' || *line == '|')
			get_token(&node, &line);
		else if (*line == '"')
			tokenize_dquote(&node, &line);
		else if (*line == '\'')
			tokenize_squote(&node, &line);
		else if (*line == '>' || *line == '<')
			tokenize_red(&node, &line);
		else if (*line == '$' && *(line + 1)
			&& (valid_var(*(line + 1)) || *(line + 1) == '?'))
			tokenize_var(&node, &line);
		else
			tokenize_word(&node, &line);
	}
	free(tmp);
	return (node);
}
