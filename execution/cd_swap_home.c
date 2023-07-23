/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_swap_home.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:44:05 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/21 17:59:07 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	home_success(t_all *all, t_pwd *p)
{
	if (p->pwd_en && p->pwd_ex)
	{
		if (!p->oldpwd_en)
			add_exen_back(&all->env, lstnew_exen(ft_strdup("OLDPWD"), \
			ft_strdup(p->pwd_en->val)));
		else
		{
			free(p->oldpwd_en->val);
			p->oldpwd_en->val = ft_strdup(p->pwd_en->val);
		}
		free (p->oldpwd_ex->val);
		p->oldpwd_ex->val = ft_strdup(p->pwd_ex->val);
	}
	if (p->pwd_en && p->pwd_ex)
	{
		if (p->pwd_en->val && p->pwd_ex->val)
		{
			free(p->pwd_en->val);
			return (p->pwd_en->val = ft_strdup(p->node->val), \
			free(p->pwd_ex->val), p->pwd_ex->val = ft_strdup(p->node->val), 0);
		}
		else
			return (ft_putstr_fd("sash: cd: PWD not set\n", 2), 0);
	}
	return (0);
}

void	cd_error(char *path, char *str)
{
	ft_putstr_fd("sash: ", 2);
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("no such file or directory\n", 2);
	}
	else if (access(path, R_OK) == -1)
		ft_putstr_fd("Permission denied\n", 2);
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("Not a directory\n", 2);
	}
}

int	cd_home(t_all *all)
{
	t_simple_cmd	*p;
	t_pwd			pwd;
	int				err;

	p = all->cmd;
	err = -1;
	pwd.node = check_char(all->exp, "HOME");
	if (!pwd.node)
		return (ft_putstr_fd("sash: cd: HOME not set\n", 2), 0);
	else
		err = chdir(pwd.node->val);
	if (err == 0)
	{
		pwd.oldpwd_en = check_char(all->env, "OLDPWD");
		pwd.pwd_en = check_char(all->env, "PWD");
		pwd.oldpwd_ex = check_char(all->exp, "OLDPWD");
		pwd.pwd_ex = check_char(all->exp, "PWD");
		home_success(all, &pwd);
	}
	else
	{
		cd_error(pwd.node->val, p->str[1]);
	}
	return (0);
}

void	swap_success(t_pwd *pwd)
{
	char	*val;

	if (!pwd->pwd_en | !pwd->pwd_ex)
		return (ft_putstr_fd("sash: cd: PWD not set\n", 2));
	else
	{
		val = ft_strdup(pwd->pwd_en->val);
		free(pwd->pwd_en->val);
		pwd->pwd_en->val = ft_strdup(pwd->oldpwd_en->val);
		free(pwd->oldpwd_en->val);
		pwd->oldpwd_en->val = ft_strdup(val);
		free(pwd->pwd_ex->val);
		pwd->pwd_ex->val = ft_strdup(pwd->oldpwd_ex->val);
		free(pwd->oldpwd_ex->val);
		pwd->oldpwd_ex->val = ft_strdup(val);
		free(val);
	}
}

int	cd_swap(t_all *all)
{
	t_simple_cmd	*p;
	t_pwd			pd;
	int				err;

	p = all->cmd;
	err = -1;
	pd.oldpwd_en = check_char(all->env, "OLDPWD");
	pd.oldpwd_ex = check_char(all->exp, "OLDPWD");
	if (!pd.oldpwd_en || !pd.oldpwd_ex)
		return (ft_putstr_fd("sash: cd: OLDPWD not set\n", 2), 0);
	else
		err = chdir(pd.oldpwd_en->val);
	if (err == 0)
	{
		pd.pwd_en = check_char(all->env, "PWD");
		pd.pwd_ex = check_char(all->exp, "PWD");
		swap_success(&pd);
		pwd(all);
	}
	else
		cd_error(pd.oldpwd_en->val, p->str[1]);
	return (0);
}
