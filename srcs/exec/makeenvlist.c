/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makeenvlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kike <kike@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:47:30 by kike              #+#    #+#             */
/*   Updated: 2021/03/02 18:54:51 by kike             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **makeenvlist(t_env *env)
{
    int i;
    char **envlist;
    t_env *tmp;

    i = 0;
    tmp = env;
    while(tmp)
    {
        i++;
        tmp = tmp->next;
    }
    envlist = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while(env)
    {
        if((envlist[i] = ft_strdup(env->vl)) == NULL)
            no_mem();
        i++;
        env = env->next;
    }
    envlist[i] = NULL;
    return (envlist);
}