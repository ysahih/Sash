/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:39:14 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/28 22:29:29 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		printf("sash: cd: %s: No such file or directory\n", p->str[1]);
	return (0);
}

int cd_previous(t_all *all)
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
		printf("sash: cd: %s: No such file or directory\n", p->str[1]);
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
		printf("sash: cd: %s: No such file or directory\n", p->str[1]);
	return (0);
}

void	cd(t_all*all)
{
	t_simple_cmd *p;

	p = all->cmd;
	if (!p->str[1] || (!ft_strcmp(p->str[1], "~")))
	{
		cd_home(all);
	}
	else if(!ft_strcmp(p->str[1], "-"))
	{
		cd_previous(all);
	}
	else
	{
		cd_else(all);
	}
}
