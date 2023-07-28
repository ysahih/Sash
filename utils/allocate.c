/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:28:18 by ysahih            #+#    #+#             */
/*   Updated: 2023/07/25 09:55:55 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_gc	*lst_garbage(t_gc *gc)
{
	if (!gc)
		return (0);
	while (gc->next)
		gc = gc->next;
	return (gc);
}

void	add_garbage( t_gc *new)
{
	t_gc	*last_garbage;
	t_gc	*tmp;

	tmp = g_gl.gc;
	if (!g_gl.gc)
	{
		g_gl.gc = new;
		return ;
	}
	last_garbage = lst_garbage(tmp);
	last_garbage->next = new;
}

void	collect_garbage(void *ptr)
{
	t_gc	*tmp;

	tmp = malloc(sizeof(t_gc));
	tmp->ptr = ptr;
	tmp->next = NULL;
	add_garbage(tmp);
}

void	*ft_malloc(int size, int flag)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (!flag)
		collect_garbage(ptr);
	return (ptr);
}

void	free_gb(void)
{
	t_gc	*tmp;

	while (g_gl.gc)
	{
		tmp = g_gl.gc;
		g_gl.gc = g_gl.gc->next;
		free(tmp->ptr);
		tmp->ptr = NULL;
		free(tmp);
		tmp = NULL;
	}
	g_gl.gc = NULL;
}
