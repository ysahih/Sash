/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:26:22 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/01 22:00:37 by kaboussi         ###   ########.fr       */
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

    str = getcwd(path, 800);
    if (!str)
        get_pwd(all);
    else if (!ft_strcmp(str, "/System/Volumes/Data"))
        printf("/\n");
    else
        printf("%s\n",str);
}