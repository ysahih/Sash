/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:28:32 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/20 14:59:46 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	egal_not_exist(t_all *all, t_simple_cmd *p, int i)
{
	t_var	*tmp_ex;

	if (is_valid(p->str[i]) == 1)
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(p->str[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}

	tmp_ex = check_char(all->exp, p->str[i]);
	if (!tmp_ex)
		add_exen_back(&all->exp, lstnew_exen(p->str[i], NULL));
	all->exp = sort_env(all->exp);
}

void	export(t_all *all)
{
	t_simple_cmd	*p;
	int				i;
	int				k;

	p = all->cmd;
	if (!p->str[1])
		only_exp(all, all->cmd->out_fd);
	else
	{
		i = 0;
		while (p->str[++i])
		{
			if (alpha(p->str[i][0]) != 1 && p->str[i][0] != '_')
			{
				ft_putstr_fd("sash: export: `", 2);
				ft_putstr_fd(p->str[i], 2);
				ft_putstr_fd("\': not a valid identifier\n", 2);
			}
			else
			{
				k = ft_strchr(p->str[i], '=');
				if (k != -1)
					exist_egal(all, p, i, k);
				else
					egal_not_exist(all, p, i);
			}
		}
	}
}