/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:26:22 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/11 19:30:12 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    get_pwd(t_all   *all)
{
    t_var   *var;

    var = all->env;
    while (var)
    {
        if (!ft_strcmp(var->key, "PWD"))
        {
            printf("%s\n", var->val);
            return ;
        }
        var = var->next;
    }
}

void    pwd(t_all   *all)
{
    char    *str;
    char    path[800];
    int     flag;

    flag = -1;
    if (all->cmd->out_fd == 1)
        flag = 1;
    else
        flag = all->cmd->out_fd;
    str = getcwd(path, 800);
    if (!str)
        get_pwd(all);
    else if (!ft_strcmp(str, "/System/Volumes/Data"))
        printf("/\n");
    else
    {
        ft_putstr_fd(str, flag);
        ft_putstr_fd("\n", flag);
    }
}