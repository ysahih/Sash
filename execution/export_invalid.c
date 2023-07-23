/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_invalid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:13:39 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/21 17:40:11 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_invalid(t_simple_cmd *p, int i)
{
	ft_putstr_fd("sash: export: `", 2);
	ft_putstr_fd(p->str[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	not_valid(t_simple_cmd *p, int i, int k)
{
	char	*invalid;
	int		j;

	invalid = ft_substr(p->str[i], 0, k);
	j = ft_strchr(invalid, '+');
	if (k - 1 == j)
	{
		free(invalid);
		invalid = ft_substr(p->str[i], 0, j);
		if (is_valid(invalid) == 1)
		{
			print_invalid(p, i);
			return (free(invalid), 1);
		}
		else
			return (free(invalid), 0);
	}
	else if (j != -1)
	{
		print_invalid(p, i);
		return (free(invalid), 1);
	}
	return (free(invalid), 2);
}

int	is_valid(char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
	{
		if (!((c[i] >= 65 && c[i] <= 90) || (c[i] >= 97 && c[i] <= 122) || \
		(c[i] >= 48 && c[i] <= 57) \
		|| (c[i] == '_') || (c[i] == '=')))
			return (1);
		i++;
	}
	return (0);
}
