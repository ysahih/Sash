/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_only.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:16:20 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/21 14:21:52 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var	*sort_env(t_var *lst)
{
	char	*key;
	char	*value;
	t_var	*p;
	t_var	*p1;

	p = lst;
	while (p)
	{
		p1 = p->next;
		while (p1)
		{
			if (ft_strcmp(p->key, p1->key) > 0)
			{
				key = p->key;
				value = p->val;
				p->key = p1->key;
				p->val = p1->val;
				p1->key = key;
				p1->val = value;
			}
			p1 = p1->next;
		}
		p = p->next;
	}
	return (lst);
}

void	only_exp(t_all *all, int flag)
{
	t_var	*tmp_ex;

	all->exp = sort_env(all->exp);
	tmp_ex = all->exp;
	while (tmp_ex)
	{
		ft_putstr_fd ("declare -x ", flag);
		ft_putstr_fd(tmp_ex->key, flag);
		if (tmp_ex->val)
		{
			ft_putstr_fd("=\"", flag);
			ft_putstr_fd(tmp_ex->val, flag);
			ft_putstr_fd("\"", flag);
		}
		ft_putstr_fd("\n", flag);
		tmp_ex = tmp_ex->next;
	}
}
