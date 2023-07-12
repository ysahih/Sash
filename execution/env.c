/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:25:49 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/11 19:29:55 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	env(t_all *all)
{
    t_var   *var;
    int     flag;

    flag = -1;
    var = all->env;
    if (all->cmd->out_fd == 1)
        flag = 1;
    else
        flag = all->cmd->out_fd;
    while (var)
    {
        // printf("%s=%s\n", var->key, var->val);
        ft_putstr_fd(var->key, flag);
        ft_putstr_fd("=", flag);
        ft_putstr_fd(var->val, flag);
        ft_putstr_fd("\n", flag);
        var = var->next;
    }
}