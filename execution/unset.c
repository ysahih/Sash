/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:07:40 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/25 13:18:40 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

    void	del(void *content)
    {
        free(content);
        content = NULL;
    }

    void	ft_lstdelone(t_list *lst, void (*del)(void*))
    {
        if (lst && del)
        {
            del(lst->content);
            free(lst);
        }
    }

// void    unset(t_all *all)
// {
//     t_simple_cmd    *p;
//     int             i;

//     while (p)
//     {
//         if (!p->str[1])
//         {
//             printf("\n");
//             return ;
//         }
//         // i = 1;
//         // if )
//     }
// }