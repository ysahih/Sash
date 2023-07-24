/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:34:47 by ysahih            #+#    #+#             */
/*   Updated: 2023/07/24 14:54:30 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_simple_cmd	*create_scmd(t_lexer *cmd)
{
	t_simple_cmd	*scmd;
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
	return (node);
}

void	collect_filenames(t_lexer **node)
{
	struct dirent	*entry;
	DIR				*dir;

	dir = NULL;
	dir = opendir(".");
	if (dir == NULL)
		perror("opendir");
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			create_node(node, entry->d_name, WORD, 0);
			create_node(node, " ", WSPACE, 0);
		}
		entry = readdir(dir);
	}
}

t_lexer	*check_for_wc(t_lexer *cmd)
{
	t_lexer	*node;

	node = NULL;
	while (cmd)
	{
		if (cmd->type == -1)
			create_node(&node, cmd->str, WORD, 0);
		else
			create_node(&node, cmd->str, cmd->type, 0);
		cmd = cmd->next;
	}
	return (node);
}

t_lexer	*parse_wc(t_lexer *cmd)
{
	t_lexer	*node;

	node = NULL;
	while (cmd)
	{
		if ((cmd->type == -1 && !cmd->next && !cmd->previous)
			|| (cmd->type == -1 && cmd->next && cmd->previous
				&& cmd->next->type == WSPACE && cmd->previous->type == WSPACE))
			collect_filenames(&node);
		else
			create_node(&node, cmd->str, cmd->type, 0);
		cmd = cmd->next;
	}
	
	node = check_for_wc(node);
	return (node);
}
