/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:50:45 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/21 14:56:58 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write (1, &str[i], 1);
        i++;
    }
}

int arg(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-')
    {
        i++;
        if (str[i] && str[i] == 'n')
        {
            while (str[i] == 'n')
            {   
                if (str[i+1] == '\0')
                    return (1);
                i++;
            }
        }
    }
    return (0);
}

void    echo(t_simple_cmd  *all)
{
    t_simple_cmd    *p;
    int             i;
    int             j;

    p = all;
    while (p)
    {
        if (!p->str[1])
        {
            printf("\n");
            return ;
        }
        i = 1;
        while (p->str[i])
        {
            if (arg(p->str[i]) == 0)
            {
                j = 1;
                while (p->str[j])
                {
                    if (p->str[j+1] == NULL)
                        printf("%s",p->str[j++]);
                    else
                        printf("%s ",p->str[j++]);
                }
                printf("\n");
                return ;
            }
            else
            {
                while (p->str[i] && arg(p->str[i]) == 1)
                    i++;
                j = i;
                while (p->str[j])
                {
                    if (p->str[j+1] == NULL)
                        printf("%s",p->str[j++]);
                    else
                        printf("%s ",p->str[j++]);
                }
                return ;
            }
            i++;
        }
        p = p->next;
    }
}