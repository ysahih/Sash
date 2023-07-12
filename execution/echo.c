/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:50:45 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/11 20:05:22 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
}

int	arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		if (str[i] && str[i] == 'n')
		{
			while (str[i] == 'n')
			{
				if (str[i + 1] == '\0')
					return (1);
				i++;
			}
		}
	}
	return (0);
}

void	exist_arg(t_all *all, t_simple_cmd *p)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = -1;
	if (all->cmd->out_fd == 1)
		flag = 1;
	else
		flag = all->cmd->out_fd; 
	if (arg(p->str[i]) == 1)
	{
		while (p->str[i] && arg(p->str[i]) == 1)
			i++;
		j = i;
		while (p->str[j])
		{
			if (p->str[j + 1] == NULL)
				ft_putstr_fd(p->str[j++], flag);
			else
			{
				ft_putstr_fd(" ", flag);
				ft_putstr_fd(p->str[j++], flag);
			}
		}
		return ;
	}
}

void	only_echo(t_all	*all, t_simple_cmd *p)
{
	int	j;
	int	i;
	int	flag;

	j = 1;
	i = 1;
	flag = -1;
	if (p->out_fd == 1)
		flag = 1;
	else
		flag = p                                                                                                                        ->out_fd;
	if (arg(p->str[i]) == 0)
	{
		while (p->str[j])
		{
			if (p->str[j + 1] == NULL)
				ft_putstr_fd(p->str[j++], flag);
			else
				ft_putstr_fd(p->str[j++], flag);
		}
		ft_putstr_fd("\n", flag);
		return ;
	}
}

void	echo(t_simple_cmd *a)
{
	t_simple_cmd	*p;
	t_all 			*all;
	int flag;

	p = a;
	flag = -1;
	if (all->cmd->out_fd == 1)
		flag = 1;
	else
		flag = all->cmd->out_fd;
	while (p)
	{
		if (!p->str[1])
		{
			ft_putstr_fd("\n", flag);
			return ;
		}
		only_echo(all, p);
		exist_arg(all, p);
		p = p->next;
	}
}