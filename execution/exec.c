/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:46:35 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/28 21:33:21 by kaboussi         ###   ########.fr       */
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
		if (!ft_strcmp(tmp->str[0], "env"))
			env(all);
		else if (!ft_strcmp(tmp->str[0], "export"))
			export(all);
		else if (!ft_strcmp(tmp->str[0], "pwd"))
			pwd(all);
		else if (!ft_strcmp(tmp->str[0], "echo"))
			echo(tmp);
		else if (!ft_strcmp(tmp->str[0] , "unset"))
			unset(tmp, &all->env, &all->exp);
		else if (!ft_strcmp(tmp->str[0], "exit"))
			ex_it (all);
		else if (!ft_strcmp(tmp->str[0], "cd"))
			cd (all);
		tmp = tmp->next;
	}
	return (0);
}
