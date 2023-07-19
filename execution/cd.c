/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:39:14 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/19 14:53:33 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	else_success(t_all *all, t_pwd *pwd, char *path)
{
	char	*val;

	if (pwd->pwd_en && pwd->pwd_ex)
	{
		val = ft_strdup(pwd->pwd_en->val);
		free(pwd->pwd_en->val);
		pwd->pwd_en->val = NULL;
		pwd->pwd_en->val = ft_strdup(getcwd(path, 800));
		if (pwd->oldpwd_en)
		{
			free(pwd->oldpwd_en->val);
			pwd->oldpwd_en->val = NULL;
			pwd->oldpwd_en->val = ft_strdup(val);
		}
		else
			add_exen_back(&all->env, lstnew_exen(ft_strdup("OLDPWD"), \
			ft_strdup(val)));
		free(pwd->pwd_ex->val);
		pwd->pwd_ex->val = NULL;
		pwd->pwd_ex->val = ft_strdup(getcwd(path, 800));
		free(pwd->oldpwd_ex->val);
		pwd->oldpwd_ex->val = NULL;
		return (pwd->oldpwd_ex->val = ft_strdup(val), free(val), 0);
	}
	return (ft_putstr_fd("sash: cd: PWD not set\n", 2), 0);
}

int	cd_else(t_all *all)
{
	t_simple_cmd	*p;
	t_pwd			pwd;
	char			path[800];

	p = all->cmd;
	if (chdir(p->str[1]) == 0)
	{
		pwd.pwd_en = check_char(all->env, "PWD");
		pwd.oldpwd_en = check_char(all->env, "OLDPWD");
		pwd.pwd_ex = check_char(all->exp, "PWD");
		pwd.oldpwd_ex = check_char(all->exp, "OLDPWD");
		else_success(all, &pwd, path);
	}
	else
		cd_error(p->str[1], p->str[1]);
	return (0);
}

void	cd(t_all *all)
{
	t_simple_cmd	*p;

	p = all->cmd;
	if (!p->str[1] || (p->str[1] && !ft_strcmp(p->str[1], "~")))
		cd_home(all);
	else if (!ft_strcmp(p->str[1], "-"))
		cd_swap(all);
	else if (!ft_strcmp(p->str[1], "."))
		curr_cd(all);
	else if (!ft_strcmp(p->str[1], ".."))
		cd_prvs(all);
	else
		cd_else(all);
}
