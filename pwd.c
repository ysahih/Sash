/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:21:39 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/21 08:25:43 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void    pwd(t_all   all)
{
	t_var	*var;

	var = all->env;
	while (var)
	{
		if (!strcmp(var, "PWD"))
		{
			printf("%s", var->val);
			return ;
		}
		var = var->next;
	}
}