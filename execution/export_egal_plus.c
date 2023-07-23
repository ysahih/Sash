/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_egal_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:48:52 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/22 17:35:37 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	just_egal(t_all *all, int i, int k, t_simple_cmd *p)
{
	t_var	*tmp_ex;
	t_var	*tmp_en;
	char	*key;

	key = ft_substr(p->str[i], 0, k);
	tmp_ex = check_char(all->exp, key);
	tmp_en = check_char(all->env, key);
	if (tmp_ex == NULL)
		add_both(all, key, "");
	else
	{
		if (tmp_ex->val)
			free(tmp_ex->val);
		tmp_ex->val = ft_strdup("");
		if (!tmp_en)
			add_exen_back(&all->env, lstnew_exen(key, tmp_ex->val));
		else
		{
			if (tmp_en->val)
				free(tmp_en->val);
			tmp_en->val = ft_strdup("");
		}
	}
	free(key);
}

int	just_egal_not_plus(t_all *all, t_simple_cmd *p, int i, int k)
{
	t_var	*tmp_ex;
	t_var	*tmp_en;
	char	*val;
	char	*key;

	key = ft_substr(p->str[i], 0, k);
	val = ft_substr(p->str[i], k + 1, ft_strlen(p->str[i]) - k);
	tmp_ex = check_char(all->exp, key);
	tmp_en = check_char(all->env, key);
	if (tmp_ex == NULL)
		return (add_both(all, key, val), free(key), free(val), 0);
	if (!tmp_en)
		add_exen_back(&all->env, \
		lstnew_exen(ft_strdup(key), ft_strdup(val)));
	else
	{
		if (tmp_en->val)
			free(tmp_en->val);
		tmp_en->val = ft_strdup(val);
	}
	if (tmp_ex->val)
		free(tmp_ex->val);
	return (tmp_ex->val = ft_strdup(val), free(key), free(val), 0);
}

int	egal_plus(t_all *all, t_simple_cmd *p, int i, int k)
{
	t_var	*tmp_ex;
	t_var	*tmp_en;
	char	*new_key;
	char	*new_val;

	new_key = ft_substr(p->str[i], 0, k - 1);
	new_val = ft_substr(p->str[i], k + 1, ft_strlen(p->str[i]) - k);
	tmp_en = check_char(all->env, new_key);
	tmp_ex = check_char(all->exp, new_key);
	if (tmp_ex != NULL)
	{
		tmp_ex->val = ft_strjoin_n(tmp_ex->val, new_val);
		if (tmp_en)
			tmp_en->val = ft_strjoin_n(tmp_en->val, new_val);
	}
	else
		add_both(all, new_key, new_val);
	tmp_en = check_char(all->env, new_key);
	if (!tmp_en)
	{
		add_exen_back(&all->env, lstnew_exen(ft_strdup(new_key), \
		ft_strdup(new_val)));
	}
	return (all->exp = sort_env(all->exp), free(new_key), free(new_val), 0);
}

void	egal_plus_empty(t_all *all, t_simple_cmd *p, int i, int k)
{
	t_var	*tmp_ex;
	char	*new_key;

	new_key = ft_substr(p->str[i], 0, k - 1);
	tmp_ex = check_char(all->exp, new_key);
	if (!tmp_ex)
	{
		add_both(all, new_key, "");
		all->exp = sort_env(all->exp);
	}
	free(new_key);
}

void	exist_egal(t_all *all, t_simple_cmd *p, int i, int k)
{
	if (not_valid(p, i, k) == 1)
	{
		return ;
	}
	if (p->str[i][k + 1] == '\0' && p->str[i][k - 1] != '+')
		just_egal(all, i, k, p);
	else if (p->str[i][k + 1] != '\0' && p->str[i][k - 1] != '+')
		just_egal_not_plus(all, p, i, k);
	else if (p->str[i][k + 1] != '\0' && p->str[i][k - 1] == '+')
		egal_plus(all, p, i, k);
	else if (p->str[i][k + 1] == '\0' && p->str[i][k - 1] == '+')
		egal_plus_empty(all, p, i, k);
}
