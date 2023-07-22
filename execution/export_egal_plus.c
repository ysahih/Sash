/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_egal_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:48:52 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/22 08:23:19 by ysahih           ###   ########.fr       */
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
		tmp_ex->val = ft_strdup("");
		if (!tmp_en)
			add_exen_back(&all->env, lstnew_exen(key, tmp_ex->val));
		else
			tmp_en->val = ft_strdup("");
	}
	
}

void	just_egal_not_plus(t_all *all, t_simple_cmd *p, int i, int k)
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
		add_both(all, key, val);
	else
	{
		if (!tmp_en)
			add_exen_back(&all->env, \
			lstnew_exen(ft_strdup(key), ft_strdup(val)));
		else
			tmp_en->val = val;
		tmp_ex->val = ft_strdup(val);
	}
}

void	egal_plus(t_all *all, t_simple_cmd *p, int i, int k)
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
		tmp_ex->val = ft_strjoin(tmp_ex->val, new_val);
		if (tmp_en)
			tmp_en->val = ft_strjoin(tmp_en->val, new_val);
	}
	else
		add_both(all, new_key, new_val);
	if (!tmp_en)
	{
		add_exen_back(&all->env, lstnew_exen(ft_strdup(new_key), \
		ft_strdup(new_val)));
	}
	all->exp = sort_env(all->exp);
}

void	egal_plus_empty(t_all *all, t_simple_cmd *p, int i, int k)
{
	t_var	*tmp_ex;
	char	*new_key;

	new_key = ft_substr(p->str[i], 0, k - 1);
	printf("{%s}\n", new_key);
	tmp_ex = check_char(all->exp, new_key);
	printf("{≥≥≥≥≥≥%s}\n", new_key);
	puts("l");
	if (!tmp_ex)
	{
		puts("k");
		add_exen_back(&all->env, lstnew_exen(new_key, ft_strdup("")));
		add_exen_back(&all->exp, lstnew_exen(ft_strdup(new_key), \
		ft_strdup("")));
		all->exp = sort_env(all->exp);
	}
}

int	is_valid(char *c)
{
	int i;

	i = 0;
	while (c[i] != '\0')
	{
		if (!((c[i] >= 65 && c[i] <= 90) || (c[i] >= 97 && c[i] <= 122) || (c[i] >= 48 && c[i] <= 57)\
		|| (c[i] == '_') || (c[i] == '=')))
			return (1);
		i++;
	}
	return (0);
}

void	exist_egal(t_all *all, t_simple_cmd *p, int i, int k)
{
	if (not_valid(p, i, k) == 1)
		return ;
	if (p->str[i][k + 1] == '\0' && p->str[i][k - 1] != '+')
		just_egal(all, i, k, p);
	else if (p->str[i][k + 1] != '\0' && p->str[i][k - 1] != '+')
		just_egal_not_plus(all, p, i, k);
	else if (p->str[i][k + 1] != '\0' && p->str[i][k - 1] == '+')
		egal_plus(all, p, i, k);
	else if (p->str[i][k + 1] == '\0' && p->str[i][k - 1] == '+')
		egal_plus_empty(all, p, i, k);
}

int	not_valid(t_simple_cmd *p, int i, int k)
{
	char *invalid;
	int j;

	invalid = ft_substr(p->str[i], 0, k);
	j = ft_strchr(invalid, '+');
	if (k - 1 == j)
	{
		invalid = ft_substr(p->str[i], 0, j);
		if (is_valid(invalid) == 1)
		{
			puts("hna");
			ft_putstr_fd("sash: export: `", 2);
			ft_putstr_fd(p->str[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		else
			return (0);
	}
	else if (j != -1)
	{
		ft_putstr_fd("sash: export: `", 2);
		ft_putstr_fd(p->str[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (2);
}
