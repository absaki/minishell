/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 23:51:31 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/19 01:36:11 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				init_senv(t_sh *sh, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc_with_list_malloc(sizeof(t_env));
	env->vl = ft_strdup_and_list_malloc(env_array[0]);
	env->next = NULL;
	sh->senv = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		new = malloc_with_list_malloc(sizeof(t_env));
		if (ft_strncmp("OLDPWD", env_array[i], 5) == 0)
			new->vl = ft_strdup_and_list_malloc("OLDPWD");
		else
			new->vl = ft_strdup_and_list_malloc(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (SUCCESS);
}

int				init_env(t_sh *sh, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc_with_list_malloc(sizeof(t_env));
	env->vl = ft_strdup_and_list_malloc(env_array[0]);
	env->next = NULL;
	sh->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		if (ft_strncmp("OLDPWD", env_array[i], 6) == 0)
		{
			i++;
			continue;
		}
		new = malloc_with_list_malloc(sizeof(t_env));
		new->vl = ft_strdup_and_list_malloc(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (SUCCESS);
}
