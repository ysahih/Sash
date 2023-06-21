/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:39:14 by kaboussi          #+#    #+#             */
/*   Updated: 2023/06/18 15:36:32 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int cd(char **str)
{
    puts("enter here");
	if (chdir(str) == 0)
    {
        return (0);
    }
    else
    {
        printf("bash: cd: ");
        printf("%s", str);
        printf(": No such file or directory\n");
        return (0);
    }
}
