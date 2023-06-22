/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:28:32 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/22 20:55:38 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var	*sort_env(t_var *lst)
{
	char *key;
    char *value;
	t_var *p;
	t_var *p1;
	t_var *tmp;

    p = lst;
    while (p)
    {
        p1 = p->next;
        while (p1)
	    {
	    	if (ft_strncmp(p->key, p1->key, 255) > 0)
	    	{
	    		key = p->key;
                value = p->val;
	    		p->key = p1->key;
                p->val = p1->val;
	    		p1->key = key;
                p1->val = value;
	    	}
            p1 = p1->next;
	    }
	    p = p->next; 
    }

	return (lst);
}

int	ft_strchr(char *str, int ch)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_substr(char *s, int start, int len)
{
	char			*p;
	int			    i;

	i = 0;
	if (!s)
		return (NULL);
	if (start < ft_strlen(s))
	{
		if (ft_strlen(s) < len)
			len = ft_strlen(s);
		p = malloc(sizeof(char) * len + 1);
		if (!p)
			return (NULL);
		while (i < len)
			p[i++] = s[start++];
	}
	else
		p = malloc(1);
	if (!p)
		return (p);
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(char *str)
{
	size_t	len;
	char	*p;
	int		i;

	len = ft_strlen(str);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (str[i])
	{
		p[i] = str[i];
		i++;
	}
	return (p);
}

t_var	*ft_last(t_var *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_var	*lstnew_exen(char  *key, char  *val)
{
	t_var	*node;

	node = malloc(sizeof(t_var));
	if (!node)
		return (NULL);
	node->key = key;
	node->val = val;
	node->next = NULL;
	return (node);
}


void	add_exen_back(t_var **exen, t_var *new)
{
	t_var	*k;
	t_var	*tmp;

	tmp = *exen;
	if (tmp)
	{
		k = ft_last(tmp);
		k->next = new;
	}
	else
		*exen = new;
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		i;
// 	int		j;
// 	size_t	len1;
// 	size_t	len2;
// 	char	*p;	

// 	if (!s1 || !s2)
// 		return (NULL);
// 	i = 0;
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	p = malloc((len1 + len2 + 1) * sizeof(char));
// 	if (!p)
// 		return (NULL);
// 	j = 0;
// 	while (s1[i])
// 	{
// 		p[j++] = s1[i++];
// 	}
// 	i = 0;
// 	while (s2[i])
// 	{
// 		p[j++] = s2[i++];
// 	}
// 	return (p);
// }

void    export(t_all *all)
{
    t_simple_cmd    *p;
    t_var           *tmp_ex;
    t_var           *tmp_en;
    t_var           *new_val;
    int i;
    int k;

    p = all->cmd;
    tmp_ex = all->exp;
    tmp_en = all->env;
    while (p)
    {
        if (!p->str[1])
        {
    		all->exp = sort_env(all->exp);
    		tmp_ex = all->exp;
            while (tmp_ex)
            {  
                printf ("declare -x ");
                printf("%s", tmp_ex->key);
                if (tmp_ex->val)
                {  
                    printf("=\"");
                    printf("%s", tmp_ex->val);
                    printf("\"");
                }
                printf("\n");
                tmp_ex = tmp_ex->next;
            }
        }
        else
        {
            i = 1;
            while(p->str[i])
            {   
                k = ft_strchr(p->str[i], '=');
                if (k != -1)
                {
                    if (p->str[i][k+1] == '\0' && p->str[i][k-1] == '+')
                    {
                        tmp_ex->key = ft_substr(p->str[i], 0, k-1);
                        tmp_ex->val = ft_strdup("");
                        add_exen_back(&all->exp ,lstnew_exen(tmp_ex->key, tmp_ex->val));
                        add_exen_back(&all->env ,lstnew_exen(tmp_ex->key, tmp_ex->val));
                        all->exp = sort_env(all->exp);
                    }
                    else if (p->str[i][k+1] == '\0')
                    {
                        tmp_ex->key = ft_substr(p->str[i], 0, k);
                        tmp_ex->val = ft_strdup("");
                        add_exen_back(&all->exp ,lstnew_exen(tmp_ex->key, tmp_ex->val));
                        add_exen_back(&all->env ,lstnew_exen(tmp_ex->key, tmp_ex->val));
                        all->exp = sort_env(all->exp);
                    }
                    else if (p->str[i][k + 1] != '\0')
                    {
                        tmp_ex->key = ft_substr(p->str[i], 0, k);
                        tmp_ex->val = ft_substr(p->str[i], k+1, ft_strlen(p->str[i])-k);
                        add_exen_back(&all->exp ,lstnew_exen(tmp_ex->key, tmp_ex->val));
                        add_exen_back(&all->env ,lstnew_exen(tmp_ex->key, tmp_ex->val));
                        all->exp = sort_env(all->exp);
                    }
                }
                else
                {
                    tmp_ex->key = p->str[i];
                    add_exen_back(&all->exp, lstnew_exen(tmp_ex->key, NULL));
                    all->exp = sort_env(all->exp);
                }
                i++;
            }
        }
        p = p->next;
    }
}
