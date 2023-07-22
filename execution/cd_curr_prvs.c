/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_curr_prvs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:48:59 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/22 10:07:31 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	curr_success(t_all *all, t_pwd *pd, char *pwd)
{
	if (!pd->oldpwd_en)
		add_exen_back(&all->env, lstnew_exen(ft_strdup("OLDPWD"), \
		ft_strdup(pwd)));
	else
	{
		free(pd->oldpwd_en->val);
		pd->oldpwd_en->val = NULL;
		pd->oldpwd_en->val = ft_strdup(pwd);
	}
	if (!pd->oldpwd_ex)
		add_exen_back(&all->exp, lstnew_exen(ft_strdup("OLDPWD"), \
		ft_strdup(pwd)));
	else
	{
		free(pd->oldpwd_ex->val);
		pd->oldpwd_ex->val = NULL;
		pd->oldpwd_ex->val = ft_strdup(pwd);
	}
	return (0);
}

int	curr_cd(t_all *all)
{
	int		i;
	char	*pwd;
	char	path[800];
	t_pwd	pd;

	pwd = getcwd(path, 800);
	if (!pwd)
	{
		printf(">>>>{%s}\n", pwd);
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		chdir(".");
		printf("{%s}\n", getcwd(path, 800));
		return (0);
	}
	i = chdir(pwd);
	if (i < 0)
		cd_error(pwd, "");
	else
	{
		pd.oldpwd_en = check_char(all->env, "OLDPWD");
		pd.oldpwd_ex = check_char(all->exp, "OLDPWD");
		curr_success(all, &pd, pwd);
	}
	return (0);
}

void	prvs_succes(t_all *all, t_pwd *pwd, char *val, char *path)
{
	if (pwd->pwd_en && pwd->pwd_en->val)
	{
		if (pwd->oldpwd_en)
		{
			free(pwd->oldpwd_en->val);
			pwd->oldpwd_en->val = NULL;
			pwd->oldpwd_en->val = ft_strdup(pwd->pwd_en->val);
		}
		else
			add_exen_back(&all->env, lstnew_exen(ft_strdup("OLDPWD"), \
			ft_strdup(pwd->pwd_en->val)));
		val = getcwd(path, 800);
		free (pwd->pwd_en->val);
		pwd->pwd_en->val = NULL;
		pwd->pwd_en->val = ft_strdup(val);
	}
	
	if (pwd->pwd_ex && pwd->pwd_ex->val)
	{
		free(pwd->oldpwd_ex->val);
		pwd->oldpwd_ex->val = NULL;
		pwd->oldpwd_ex->val = ft_strdup(pwd->pwd_ex->val);
		val = getcwd(path, 800);
		unset_exp("PWD", &all->exp);
		add_exen_back(&all->exp, lstnew_exen(ft_strdup("PWD"), ft_strdup(val)));
	}
}

int	prvs_to_home(t_pwd *pwd, char *val)
{
	if (pwd->pwd_en && pwd->pwd_en->val)
	{
		free(pwd->pwd_en->val);
		pwd->pwd_en->val = NULL;
		pwd->pwd_en->val = ft_strdup("/");
		free(pwd->oldpwd_en->val);
		pwd->oldpwd_en->val = NULL;
		pwd->oldpwd_en->val = ft_strdup(val);
	}
	if (pwd->pwd_ex && pwd->pwd_ex->val)
	{
		free(pwd->pwd_ex->val);
		pwd->pwd_ex->val = NULL;
		pwd->pwd_ex->val = ft_strdup("/");
		free(pwd->oldpwd_ex->val);
		pwd->oldpwd_ex->val = NULL;
		pwd->oldpwd_ex->val = ft_strdup(val);
	}
	chdir("..");
	return (0);
}

int	cd_prvs(t_all *all)
{
	t_simple_cmd	*p;
	t_pwd			pwd;
	char			path[801];
	char			*val;

	p = all->cmd;
	pwd.pwd_en = check_char(all->env, "PWD");
	pwd.oldpwd_en = check_char(all->env, "OLDPWD");
	pwd.pwd_ex = check_char(all->exp, "PWD");
	pwd.oldpwd_ex = check_char(all->exp, "OLDPWD");
	val = getcwd(path, 800);
	if (!val)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (0);
	}
	if (!ft_strcmp(val, "/Users"))
		prvs_to_home(&pwd, val);
	if (chdir("..") == 0)
		prvs_succes(all, &pwd, val, path);
	else
		perror("cd");
	return (0);
}
