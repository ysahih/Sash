/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:28:32 by kaboussi          #+#    #+#             */
/*   Updated: 2023/07/06 14:32:23 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var	*sort_env(t_var *lst)
{
	char *key;
    char *value;
	t_var *p;
	t_var *p1;
	// t_var *tmp;

    p = lst;
    while (p)
    {
        p1 = p->next;
        while (p1)
	    {
	    	if (ft_strcmp(p->key, p1->key) > 0)
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
		k = check_char(tmp, new->key);
		if (k != NULL)
		{
			if (!ft_strcmp(k->val, new->val))
			{
				return ;
			}
		}
		k = ft_last(tmp);
		k->next = new;
	}
	else
		*exen = new;
}

t_var	*check_char(t_var	*env, char	*str)
{
	while (env)
	{
		if (!ft_strcmp(env->key, str))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

void    export(t_all *all)
{
    t_simple_cmd    *p;
    t_var           *tmp_ex;
    t_var           *tmp_en;
    char           *new_val;
    char           *new_key;
    char           *key;
    char           *val;
    int i;
    int k;
    int j;

    p = all->cmd;
    tmp_ex = all->exp;
    tmp_en = all->env;
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
			if (isalpha(p->str[i][0]) != 1 && p->str[i][0] != '_')
			{
				printf("sash$ ");
				printf("%s:", p->str[i]);
				printf(" command not found\n");
			}
            k = ft_strchr(p->str[i], '=');
            j = ft_strchr(p->str[i], '+');
            if (k != -1)
            {
				key = ft_substr(p->str[i], 0, k);
				tmp_ex = check_char(all->exp, key);
				tmp_en = check_char(all->env, key);
                if (p->str[i][k+1] == '\0')
                {
					if (tmp_ex == NULL)
					{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
                		add_exen_back(&all->exp ,lstnew_exen(key, ft_strdup("")));
                		add_exen_back(&all->env ,lstnew_exen(ft_strdup(key), ft_strdup("")));
					}
					else
					{
						tmp_ex->val = ft_strdup("");
						if (!tmp_en)
							add_exen_back(&all->env ,lstnew_exen(key, tmp_ex->val));
						else
							tmp_en->val = ft_strdup("");
							
					}
				}
                else if (p->str[i][k + 1] != '\0' && p->str[i][k-1] != '+')
                {
					key = ft_substr(p->str[i], 0, k);
					val = ft_substr(p->str[i], k+1, ft_strlen(p->str[i])-k);  
					tmp_ex = check_char(all->exp, key);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
					tmp_en = check_char(all->env, key);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
					if (tmp_ex == NULL)
					{
                		add_exen_back(&all->exp ,lstnew_exen(key, val));
                		add_exen_back(&all->env ,lstnew_exen(ft_strdup(key), ft_strdup(val)));
					}
					else
					{
						if (!tmp_en)
                			add_exen_back(&all->env ,lstnew_exen(ft_strdup(key), ft_strdup(val)));
						else
							tmp_en->val = val;
						tmp_ex->val = ft_strdup(val);
					}
                }
				else if (p->str[i][k+1] != '\0' && p->str[i][k - 1] == '+')
				{
					new_key = ft_substr(p->str[i], 0, k-1);
					new_val = ft_substr(p->str[i], k+1, ft_strlen(p->str[i])-k);
					tmp_en = check_char(all->env, new_key);
					tmp_ex = check_char(all->exp, new_key);
					if (tmp_ex != NULL)
					{
						tmp_ex->val = ft_strjoin(tmp_ex->val, new_val);
						if (tmp_en)
							tmp_en->val = ft_strjoin(tmp_en->val, new_val);
						else
							add_exen_back(&all->env ,lstnew_exen(ft_strdup(new_key), ft_strdup(new_val)));
					}
					else
					{
						tmp_ex->val = ft_substr(p->str[i], k+1, ft_strlen(p->str[i])-k);
						if (tmp_en)
							tmp_en->val = ft_substr(p->str[i], k+1, ft_strlen(p->str[i])-k);
						else
							add_exen_back(&all->env ,lstnew_exen(ft_strdup(new_key), ft_strdup(new_val)));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
					}
					all->exp = sort_env(all->exp);
				}
				else if (p->str[i][k+1] == '\0' && p->str[i][k - 1] == '+')
				{
					new_key = ft_substr(p->str[i], 0, k-1);
					tmp_ex = check_char(all->exp, new_key);
					if (!tmp_ex)
					{
						add_exen_back(&all->env ,lstnew_exen(new_key, ft_strdup("")));
						add_exen_back(&all->exp ,lstnew_exen(ft_strdup(new_key), ft_strdup("")));
						all->exp = sort_env(all->exp);
					}
				}
            }
            else
            {
				tmp_ex = check_char(all->exp, p->str[i]);
				if (!tmp_ex)
                	add_exen_back(&all->exp, lstnew_exen(p->str[i], NULL));
                all->exp = sort_env(all->exp);
            }
            i++;
        }
    }
}
