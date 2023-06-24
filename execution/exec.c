/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:46:35 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/24 13:28:07 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec(t_all *all)
{
	int i;
	t_simple_cmd *tmp;
	
	i = 0;
	tmp = all->cmd;
	if (!*(tmp->str))
		return (0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->str[0], "env", 255))
			env(all);
		else if (!ft_strncmp(tmp->str[0], "export", 255))
			export(all);
		else if (!ft_strncmp(tmp->str[0], "pwd", 255))
			pwd(all);
		else if (!strncmp(tmp->str[0], "echo", 255))
			echo(tmp);
		// if (!ft_strncmp(cmd->str, "cd", 255))
		// {
		// 	// puts("here");
		// 	// if (!cmd->next->next->str) {
		// 	// 	puts("strcmp");
		// 	// 	return 0;
		// 	// }
		// 	// cd(cmd->next->next->str);
		// 	// return (0);
		// }
		tmp = tmp->next;
	}
	return (0);
}