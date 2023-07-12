/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:03:37 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/11 19:30:43 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *st1, char *st2)
{
	size_t			i;

	i = 0;

	if (st1 == NULL)
	{
		return (-1);
	}
	else if (st2 == NULL)
	{
		return (1);
	}
	while (st1[i] != '\0' || st2[i] != '\0')
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

