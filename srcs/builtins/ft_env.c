/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:36:35 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/19 01:34:32 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(char **args, t_env *env)
{
	// unsetフラグの変更
	// 引数の変更
	if (args[1])
	{
		ft_putstr_fd("env: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		return (ERROR);
	}
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->vl, 1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->vl, 1);
	return (SUCCESS);
}
