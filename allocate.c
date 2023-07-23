#include "minishell.h"

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

	tmp = gl.gc;
	if (!gl.gc)
	{
		gl.gc = new;
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

	while (gl.gc)
	{
		tmp = gl.gc;
		gl.gc = gl.gc->next;
		free(tmp->ptr);
		free(tmp);
	}
	gl.gc = NULL;
}
