/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:25:49 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/22 14:04:00 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	env(t_all *all)
{
    t_var   *var;

    var = all->env;
    while (var)
    {
        printf("%s=%s\n", var->key, var->val);
        var = var->next;
    }
}