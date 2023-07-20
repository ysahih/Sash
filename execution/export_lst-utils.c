/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_lst-utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:12:45 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/19 15:15:27 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var	*ft_last(t_var *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_var	*lstnew_exen(char *key, char *val)
{
	t_var	*node;

	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->key = key;
	node->val = val;
	node->next = NULL;
	return (node);
}

void	add_exen_back(t_var **exen, t_var *new)
{
	t_var	*k;
	t_var	*tmp;

	tmp = *exen;
	if (tmp)
	{
		k = check_char(tmp, new->key);
		if (k != NULL)
		{
			if (!ft_strcmp(k->val, new->val))
			{
				return ;
			}
		}
		k = ft_last(tmp);
		k->next = new;
	}
	else
		*exen = new;
}

void	add_both(t_all *all, char *key, char *val)
{
	add_exen_back(&all->exp, lstnew_exen(ft_strdup(key), ft_strdup(val)));
	add_exen_back(&all->env, lstnew_exen(ft_strdup(key), ft_strdup(val)));
}

t_var	*check_char(t_var *env, char *str)
{
	while (env)
	{
		if (!ft_strcmp(env->key, str))
			return (env);
		env = env->next;
	}
	return (NULL);
}