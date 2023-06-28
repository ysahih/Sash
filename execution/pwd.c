/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:26:22 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/26 18:45:37 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    pwd(t_all   *all)
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