/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makeenvlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:47:30 by kike              #+#    #+#             */
/*   Updated: 2021/03/14 18:42:02 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**makeenvlist(t_env *env)
{
	int		i;
	char	**envlist;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envlist = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		if ((envlist[i] = ft_strdup(env->vl)) == NULL)
			no_mem();
		i++;
		env = env->next;
	}
	envlist[i] = NULL;
	return (envlist);
}
