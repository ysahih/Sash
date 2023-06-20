/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:46:35 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/20 15:20:07 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec(t_all *all)
{
	int i;
	t_simple_cmd *tmp;
	
	i = 0;
	tmp = all->cmd;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str[0], "env", 255))
		{
			env(all->env);
		}
		else if (!ft_strncmp(tmp->str[0], "export", 255))
		{
			export(all);
		}
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