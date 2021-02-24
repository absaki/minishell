/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:36:35 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/24 13:49:22 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		ft_env_print_error(char **args)
{
	ft_putstr_fd("env: ", STDERR);
	ft_putstr_fd(args[1], STDERR);
	ft_putendl_fd(": No such file or directory", STDERR);
	return (ERROR);
}

static	void	ft_env_put(t_env *env, int unset_pwd, int unset_oldpwd)
{
	if (ft_strncmp(env->vl, "PWD", 3) == 0)
	{
		if (unset_pwd == 0)
			ft_putendl_fd(env->vl, 1);
	}
	else if (ft_strncmp(env->vl, "OLDPWD", 6) == 0)
	{
		if (unset_oldpwd == 0)
			ft_putendl_fd(env->vl, 1);
	}
	else
		ft_putendl_fd(env->vl, 1);
}

int				ft_env(char **args, t_env *env, int unset_pwd, int unset_oldpwd)
{
	if (args[1])
		return (ft_env_print_error(args));
	while (env && env->next != NULL)
	{
		if (unset_pwd == 1 && ft_strncmp(env->vl, "PWD", 3) == 0)
		{
			env = env->next;
			continue;
		}
		if (unset_oldpwd == 1 && ft_strncmp(env->vl, "OLDPWD", 6) == 0)
		{
			env = env->next;
			continue;
		}
		ft_putendl_fd(env->vl, 1);
		env = env->next;
	}
	if (env)
	{
		ft_env_put(env, unset_pwd, unset_oldpwd);
	}
	return (SUCCESS);
}
