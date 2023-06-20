/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:28:32 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/20 19:51:28 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	sort_env(t_var *lst)
{
	t_var *tmp;
	t_var *p;
	t_var *p1;

    p = lst;
    while (p)
    {
        p1 = p->next;
        while (p1)
	    {
	    	if (ft_strncmp(p->key, p1->key, 255) > 0)
	    	{
	    		tmp = p;
	    		p = p1;
	    		p1 = tmp;
	    	}
            p1 = p1->next;
	    }
	    p = p->next;
    }
}

int	ft_strchr(char *str, int ch)
{
	int		i;

	i = 0;
	// if (ch == 0)
    // {
    //     j = str + ft_strlen(str);
	// 	// return (j = ptr + ft_strlen(ptr));
    // }
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)ch)
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

void    export(t_all *all)
{
    t_simple_cmd    *p;
    t_var           *tmp;
    int i;
    int j;
    int k;

    p = all->cmd;
    tmp = all->exp;
    while (p)
    {
        if (!p->str[1])
        {
            while (tmp)
            {  
                printf ("declare -x ");
                printf("%s", tmp->key);
                if (tmp->val)
                {  
                    printf("=\"");
                    printf("%s", tmp->val);
                    printf("\"");
                }
                printf("/n");
                tmp = tmp->next;
            }
        }
        else
        {
            i = 1;
            while(p->str[i])
            {
                k = ft_strchr(p->str[i], '=');
                j = 0;
                while (p->str[i][j])
                {
                    if (k != -1)
                    {
                        if (p->str[i][j-1] == '=')
                        {
                            tmp->key = ft_substr(p->str[i], 0, k-0+1);
                            tmp->val = ft_strdup("");
                        }
                        else if (p->str[i][j-1] != '=')
                        {
                            tmp->key = ft_substr(p->str[i], 0, k-0+1);
                            tmp->val = ft_substr(p->str[i], k+1, ft_strlen(p->str[i])-k);
                        }
                    }
                    else
                    {
                        tmp->key = p->str[i];
                    }                 
                }           
            }
        }
        p = p->next;
    }
}

// t_lexer	*ft_lstnew(void *content)
// {
// 	t_lexer	*k;

// 	k = malloc(sizeof(t_lexer));
// 	if (!k)
// 		return (NULL);
// 	k->content = content;
// 	k->next = NULL;
// 	return (k);
// }

// int main()
// {
//     t_lexer *lst;
//     lst = NULL;
//     ft_lstadd_back(&lst, create_node("
//     ft_lstadd_back(&lst, create_node("
//     ft_lstadd_back(&lst, create_node("
// }