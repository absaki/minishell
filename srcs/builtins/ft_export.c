/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:14:24 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/19 00:44:53 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_in_export(char *arg)
{
	ft_putstr_fd("bash: export: `", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd("': not a valid identifier", STDERR);
}

static void	check_in_env_and_add(char **args, t_env *env, int i)
{
	if (is_in_env(env, args[i]) == SUCCESS)
		env_add(args[i], env);
}

static	int	ft_export_loop(char **args, t_env *env, t_env *secret)
{
	int		i;
	int		flag_error;

	i = 1;
	while (args[i])
	{
		if (is_valid_env(args[i]) < 0)
		{
			flag_error = 1;
			print_error_in_export(args[i]);
		}
		else
		{
			if (!(ft_strchr(args[i], '=')))
				env_add(args[i], secret);
			else
			{
				check_in_env_and_add(args, env, i);
				check_in_env_and_add(args, secret, i);
			}
		}
		i++;
	}
	return (flag_error);
}

int			ft_export(char **args, t_env *env, t_env *secret)
{
	int		flag_error;

	// 引数の変更
	// unsetフラグの変更
	flag_error = 0;
	if (!args[1])
	{
		print_sorted_env(secret);
		return (SUCCESS);
	}
	else
		flag_error = ft_export_loop(args, env, secret);
	if (flag_error == 1)
		return (ERROR);
	else
		return (SUCCESS);
}
