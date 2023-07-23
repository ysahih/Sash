/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notbuiltin_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:41:23 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/21 14:42:47 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_not_found(char **path, char **k, char *join, t_simple_cmd *p)
{
	ft_freee(path);
	ft_freee(k);
	free(join);
	ft_putstr_fd("sash: ", 2);
	ft_putstr_fd(p->str[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

int	my_atoi(char *str)
{
	int	i;
	int	s;
	int	n;

	s = 1;
	i = 0;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			(s *= -1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + str[i] - 48;
		i++;
	}
	return (n * s);
}

void	shelvl(t_all *all, t_simple_cmd *p)
{
	t_var	*shelvl_ex;
	t_var	*shelvl_en;
	int		new;
	char	*str;

	if (!ft_strcmp(p->str[0], "./sash"))
	{
		shelvl_en = check_char(all->env, "SHLVL");
		shelvl_ex = check_char(all->exp, "SHLVL");
		dup2(p->in_fd, 0);
		dup2(p->out_fd, 1);
		new = my_atoi(shelvl_en->val);
		new++;
		free (shelvl_en->val);
		free (shelvl_ex->val);
		str = ft_itoa(new);
		shelvl_en->val = NULL;
		shelvl_en->val = ft_strdup(str);
		shelvl_ex->val = NULL;
		shelvl_ex->val = ft_strdup(str);
	}
}

void	check_path(t_var *key, char **k, t_simple_cmd *p)
{
	int		i;
	char	*join;
	char	**path;

	path = ft_split_path(key->val);
	if (!strchr(p->str[0], '/'))
	{
		i = 0;
		while (path[i])
		{
			join = ft_strjoin(path[i], "/");
			join = ft_strjoin_n(join, p->str[0]);
			if (access(join, R_OK) == 0)
			{
				ft_freee(path);
				execve(join, p->str, k);
			}
			free(join);
			i++;
		}
		cmd_not_found(path, k, join, p);
	}
	ft_freee(path);
	execve(p->str[0], p->str, k);
}
