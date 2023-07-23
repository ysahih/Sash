/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:34:25 by ysahih            #+#    #+#             */
/*   Updated: 2023/07/23 17:34:26 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

char	*set_line(t_lexer **node, char **line)
{
	char	*tmp;

	tmp = *line;
	*node = NULL;
	while (is_ws(**line))
		(*line)++;
	return (tmp);
}
