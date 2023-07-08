/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:39:14 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/06 19:15:44 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_error(char *path, char *str)
{
	ftputstr("sash: ");
	if (access(path, F_OK) == -1)
	{
		ftputstr("cd: ");
		ftputstr(str);
		ftputstr(": ");
		ftputstr("no such file or directory\n");
	}
	else if (access(path, R_OK) == -1)
		ftputstr("Permission denied\n");
	else
	{
		ftputstr("cd: ");
		ftputstr(str);
		ftputstr(": ");
		ftputstr("Not a directory\n");
	}
}

int cd_home(t_all *all)
{
	t_simple_cmd	*p;
	t_var			*node;
	t_var			*pwd_en;
	t_var			*oldpwd_en;
	t_var			*pwd_ex;
	t_var			*oldpwd_ex;
	int				err;

	p = all->cmd;
	err = -1;
	node = check_char(all->exp, "HOME");
	if (!node)
		return (printf("sash: cd: HOME not set\n"));
	else
		err = chdir(node->val);
	if (err == 0)
	{
		oldpwd_en = check_char(all->env, "OLDPWD");
		pwd_en = check_char(all->env, "PWD");
		oldpwd_ex = check_char(all->exp, "OLDPWD");
		pwd_ex = check_char(all->exp, "PWD");
		if (pwd_en && pwd_ex)
		{
			//env
			if (!oldpwd_en)
				add_exen_back(&all->env ,lstnew_exen(ft_strdup("OLDPWD"), ft_strdup(pwd_en->val)));
			else
			{
				free(oldpwd_en->val);
				oldpwd_en->val = ft_strdup(pwd_en->val);
			}
			//exp
			free (oldpwd_ex->val);
			oldpwd_ex->val = ft_strdup(pwd_ex->val);
		}
		if (pwd_en && pwd_ex)
		{
			if (pwd_en->val && pwd_ex->val)
			{
				//env
				free(pwd_en->val);
				pwd_en->val = ft_strdup(node->val);
				//exp
				free(pwd_ex->val);
				pwd_ex->val = ft_strdup(node->val);
			}
			else
				return (printf("sash: cd: PWD not set\n"));
		}
	}
	else
		cd_error(node->val, p->str[1]);
	return (0);
}

int cd_swap(t_all *all)
{
	t_simple_cmd	*p;
	t_var			*pwd_en;
	t_var			*oldpwd_en;
	t_var			*pwd_ex;
	t_var			*oldpwd_ex;
	char			*val;
	int				err;

	p = all->cmd;
	err = -1;
	oldpwd_en = check_char(all->env, "OLDPWD");
	oldpwd_ex = check_char(all->exp, "OLDPWD");
	if (!oldpwd_en || !oldpwd_ex)
		return (printf("sash: cd: OLDPWD not set\n"));
	else
		err = chdir(oldpwd_en->val);
	if (err == 0)
	{
		pwd_en = check_char(all->env, "PWD");
		pwd_ex = check_char(all->exp, "PWD");
		if (!pwd_en | ! pwd_ex)
			return (printf("sash: cd: PWD not set\n"));
		else
		{
			//env
			val = ft_strdup(pwd_en->val);
			free(pwd_en->val);
			pwd_en->val = ft_strdup(oldpwd_en->val);
			free(oldpwd_en->val);
			oldpwd_en->val = ft_strdup(val);
			//exp
			free(pwd_ex->val);
			pwd_ex->val = ft_strdup(oldpwd_ex->val);
			free(oldpwd_ex->val);
			oldpwd_ex->val = ft_strdup(val);
			free(val);
		}
	}
	else
		cd_error(oldpwd_en->val, p->str[1]);
	return (0);
}

int cd_else(t_all *all)
{
	t_simple_cmd	*p;
	t_var			*pwd_en;
	t_var			*oldpwd_en;
	t_var			*pwd_ex;
	t_var			*oldpwd_ex;
	char			*val;
	char			path[800];

	p = all->cmd;
	if (chdir(p->str[1]) == 0)
	{
		pwd_en = check_char(all->env, "PWD");
		oldpwd_en = check_char(all->env, "OLDPWD");
		pwd_ex = check_char(all->exp, "PWD");
		oldpwd_ex = check_char(all->exp, "OLDPWD");
		if (pwd_en && pwd_ex)
		{
			//env
			val = ft_strdup(pwd_en->val);
			free(pwd_en->val);
			pwd_en->val = ft_strdup(getcwd(path, 800));
			free(oldpwd_en->val);
			oldpwd_en->val = ft_strdup(val);
			//exp
			free(pwd_ex->val);
			pwd_ex->val = ft_strdup(getcwd(path, 800));
			free(oldpwd_ex->val);
			oldpwd_ex->val = ft_strdup(val);
			free(val);
		}
		else
			return (printf("sash: cd: PWD not set\n"));
	}
	else
		cd_error(p->str[1], p->str[1]);
	return (0);
}


int curr_cd(t_all *all)
{
	int				i;
	char			*pwd;
   	char			path[800];
	t_var			*oldpwd_en;
	t_var			*oldpwd_ex;

    pwd = getcwd(path, 800);
	if (!pwd)
	{
		ftputstr("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		return (0);
	}
	i = chdir(pwd);
    if(i < 0)
		cd_error(pwd, "");
	else
	{
		oldpwd_en = check_char(all->env, "OLDPWD");
		oldpwd_ex = check_char(all->exp, "OLDPWD");
		if (!oldpwd_en)
			add_exen_back(&all->env ,lstnew_exen(ft_strdup("OLDPWD"), ft_strdup(pwd)));
		if (!oldpwd_ex)
			add_exen_back(&all->exp ,lstnew_exen(ft_strdup("OLDPWD"), ft_strdup(pwd)));
		else
			oldpwd_ex->val = ft_strdup(pwd);
	}
    return (0);
}

int ft_strrchr(char *str, char c)
{
    int i;

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

int cd_prvs(t_all *all)
{
	t_simple_cmd	*p;
    t_var   		*pwd_ex;
    t_var   		*oldpwd_ex;
	t_var   		*pwd_en;
    t_var   		*oldpwd_en;
    char    		path[800];
    char    		*val;

	p = all->cmd;
	pwd_en = check_char(all->env, "PWD");
	oldpwd_en = check_char(all->env, "OLDPWD");
	pwd_ex = check_char(all->exp, "PWD");
	oldpwd_ex = check_char(all->exp, "OLDPWD");
	val = getcwd(path, 800);
	if (!ft_strcmp(val, "/System/Volumes/Data"))
	{
		if (pwd_en && pwd_en->val)
		{
			free(pwd_en->val);
			pwd_en->val = ft_strdup("/");
		}
		if (pwd_ex && pwd_ex->val)
		{
			free(pwd_ex->val);
			pwd_ex->val = ft_strdup("/");
		}
		return (0);
	}
	if (chdir("..") == 0)
	{
		if (pwd_en && pwd_en->val)
		{
			if (oldpwd_en)
			{
				free(oldpwd_en->val);
				oldpwd_en->val = ft_strdup(val);
				free (pwd_en->val);
				pwd_en->val = ft_strdup(getcwd(path, 800));
			}
			else
			{
				add_exen_back(&all->env ,lstnew_exen(ft_strdup("OLDPWD"), ft_strdup(pwd_en->val)));
				free (pwd_en->val);
				pwd_en->val = ft_strdup(getcwd(path, 800));
			}
		}
		if (pwd_ex && pwd_ex->val)
		{
			if (oldpwd_ex->val)
				free(oldpwd_ex->val);
			oldpwd_ex->val = ft_strdup(pwd_ex->val);
			free (pwd_ex->val);
			pwd_ex->val = ft_strdup(getcwd(path, 800));
		}
	}
	else
		perror("cd");
    return (0);
}

void	cd(t_all*all)
{
	t_simple_cmd *p;

	p = all->cmd;
	if (!p->str[1] || (p->str[1] && !ft_strcmp(p->str[1], "~")))
		cd_home(all);
	else if(!ft_strcmp(p->str[1], "-"))
		cd_swap(all);
    else if (!ft_strcmp(p->str[1], "."))
        curr_cd(all);
    else if (!ft_strcmp(p->str[1], ".."))
        cd_prvs(all);
	else
		cd_else(all);
}
