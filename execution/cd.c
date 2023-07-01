/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:39:14 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/01 22:02:09 by kaboussi         ###   ########.fr       */
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
	t_var			*pwd;
	t_var			*old_pwd;
	int				err;
	
	err = -1;
	p = all->cmd;
	if (!p->str[1] || (!ft_strcmp(p->str[1], "~")))
	{
		node = check_char(all->env, "HOME");
		if (!node)
			printf("sash: cd: HOME not set\n");
		else
			err = chdir(node->val);
	}
	if (err == 0)
	{
		old_pwd = check_char(all->env, "OLDPWD");
		pwd = check_char(all->env, "PWD");
		if (pwd)
		{
			free (old_pwd->val);
			old_pwd->val = ft_strdup(pwd->val);
		}
		if (pwd)
		{
			if (pwd->val)
			{
				free(pwd->val);
				pwd->val = ft_strdup(node->val);
			}
			else
				printf("sash: cd: PWD not set\n");
		}
	}
	else
		cd_error(node->val, p->str[1]);
	return (0);
}

int cd_swap(t_all *all)
{
	t_simple_cmd	*p;
	t_var			*pwd;
	t_var			*old_pwd;
	char			*val;
	int				err;

	err = -1;
	p = all->cmd;
	if (!ft_strcmp(p->str[1], "-"))
	{
		old_pwd = check_char(all->env, "OLDPWD");
		if (!old_pwd)
			printf("bash: cd: OLDPWD not set\n");
		else
			err = chdir(old_pwd->val);
	}
	if (err == 0)
	{
		pwd = check_char(all->env, "PWD");
		if (!pwd)
			printf("bash: cd: PWD not set\n");
		else
		{
			val = ft_strdup(pwd->val);
			free(pwd->val);
			pwd->val = ft_strdup(old_pwd->val);
			free(old_pwd->val);
			old_pwd->val = val;
		}
	}
	else
		cd_error(old_pwd->val, p->str[1]);
	return (0);
}

int cd_else(t_all *all)
{
	t_simple_cmd	*p;
	t_var			*pwd;
	t_var			*old_pwd;
	char			*val;

	p = all->cmd;
	if (chdir(p->str[1]) == 0)
	{
		pwd = check_char(all->env, "PWD");
		old_pwd = check_char(all->env, "OLDPWD");
		if (pwd)
		{
			val = ft_strdup(pwd->val);
			pwd->val = ft_strjoin(pwd->val, "/");
			pwd->val = ft_strjoin(pwd->val, p->str[1]);
			free(old_pwd->val);
			old_pwd->val = val;
		}
		else
			printf("sash: cd: PWD not set\n");
	}
	else
		cd_error(p->str[1], p->str[1]);
	return (0);
}


int curr_cd(t_all *all)
{
    t_simple_cmd    *p;
	int				i;
	char			*pwd;
   	char			 path[800];

    p = all->cmd;
    pwd = getcwd(path, 800);
	if (!pwd)
	{
		ftputstr("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		return (0);
	}
	i = chdir(pwd);
    if(i < 0)
		cd_error(pwd, "");
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
    // int 			i;
	t_simple_cmd	*p;
    t_var   		*pwd;
    t_var   		*old_pwd;
    char    		path[800];
    char    		*val;

	p = all->cmd;
	pwd = check_char(all->env, "PWD");
	old_pwd = check_char(all->env, "OLDPWD");
    // i = ft_strrchr(pwd->val, '/');
    // path = ft_substr(pwd->val, 0, i);
	// if (!ft_strcmp(path, "/Users"))
	// {
	// 	free(pwd->val);
	// 	pwd->val = ft_strdup("/");
	// 	return (0);
	// }
    // if (chdir(path) == -1)
    //     cd_error(path, p->str[1]);
    // else
    // {
	// 	val = ft_strdup(pwd->val);
    //     free (pwd->val);
    //     pwd->val = path;
    //     free(old_pwd->val);
    //     old_pwd->val = val;
    // }
	val = getcwd(path, 800);
	if (!ft_strcmp(val, "/System/Volumes/Data"))
	{
		free(pwd->val);
		pwd->val = ft_strdup("/");
		// return (0);
	}
	if (chdir("..") == 0)
	{
		free(old_pwd->val);
        old_pwd->val = ft_strdup(val);
		free (pwd->val);
        pwd->val = ft_strdup(getcwd(path, 800));
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
