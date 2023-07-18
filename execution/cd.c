/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:39:14 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/14 08:38:55 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	home_success(t_all *all, t_pwd *pwd)
{
	if (pwd->pwd_en && pwd->pwd_ex)
	{
		if (!pwd->oldpwd_en)
			add_exen_back(&all->env, lstnew_exen(ft_strdup("OLDPWD"), \
			ft_strdup(pwd->pwd_en->val)));
		else
		{
			free(pwd->oldpwd_en->val);
			pwd->oldpwd_en->val = ft_strdup(pwd->pwd_en->val);
		}
		free (pwd->oldpwd_ex->val);
		pwd->oldpwd_ex->val = ft_strdup(pwd->pwd_ex->val);
	}
	if (pwd->pwd_en && pwd->pwd_ex)
	{
		if (pwd->pwd_en->val && pwd->pwd_ex->val)
		{
			free(pwd->pwd_en->val);
			pwd->pwd_en->val = ft_strdup(pwd->node->val);
			free(pwd->pwd_ex->val);
			pwd->pwd_ex->val = ft_strdup(pwd->node->val);
		}
		else
			return (ft_putstr_fd("sash: cd: PWD not set\n", 2), 0);
	}
	return (0);
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
		// printf("pwd_en: %s\n", pwd.pwd_en->val);
		// printf("pwd_ex: %s\n", pwd.pwd_ex->val);
		// printf("oldpwd_en: %s\n", pwd.oldpwd_en->val);
		// printf("oldpwd_ex: %s\n", pwd.oldpwd_ex->val);
		home_success(all, &pwd);
		// printf("\n\npwd_en: %s\n", pwd.pwd_en->val);
		// printf("pwd_ex: %s\n", pwd.pwd_ex->val);
		// printf("oldpwd_en: %s\n", pwd.oldpwd_en->val);
		// printf("oldpwd_ex: %s\n", pwd.oldpwd_ex->val);
	}
	else
	{
		cd_error(pwd.node->val, p->str[1]);
	}
	return (0);
}

void	swap_success(t_all *all, t_pwd *pwd)
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
	char			*val;
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
		swap_success(all, &pd);
		pwd(all);
	}
	else
		cd_error(pd.oldpwd_en->val, p->str[1]);
	return (0);
}

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
	char			*val;
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
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
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

int	ft_strrchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (0);
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

int	prvs_succes(t_all *all, t_pwd *pwd, char *val, char *path)
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
