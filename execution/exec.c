/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:46:35 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/25 11:56:18 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec(t_all *all)
{
	int i;
	t_simple_cmd *tmp;
	
	i = 0;
	if (!all->cmd)
		return (0);
	tmp = all->cmd;
	if (!*(tmp->str))
		return (0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->str[0], "env"))
			env(all);
		else if (!ft_strncmp(tmp->str[0], "export"))
			export(all);
		else if (!ft_strncmp(tmp->str[0], "pwd"))
			pwd(all);
		else if (!ft_strncmp(tmp->str[0], "echo"))
			echo(tmp);
		// else if (!ft_strncmp(tmp->str[0] , "unset"))
		// 	unset(all);
		else if (!ft_strncmp(tmp->str[0], "exit"))
			exit (0);
		// if (!ft_strncmp(cmd->str, "cd"))
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