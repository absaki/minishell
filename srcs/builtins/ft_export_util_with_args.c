/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util_with_args.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 19:02:37 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/23 19:16:18 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_error_in_export(char *arg)
{
	ft_putstr_fd("bash: export: `", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd("': not a valid identifier", STDERR);
}

static void		check_in_env_and_add(char *str, t_env *env, t_sh *sh, int opt)
{
	char	var_name[BUFF_SIZE];

	get_env_name(var_name, str);
	if (opt == 1)
	{
		if (ft_strcmp(var_name, "PWD") == 0)
			sh->unset_pwd = 0;
		if (ft_strcmp(var_name, "OLDPWD") == 0)
			sh->unset_oldpwd = 0;
	}
	if (ft_strcmp(var_name, "PWD") == 0)
		sh->unset_pwd_s = 0;
	if (ft_strcmp(var_name, "OLDPWD") == 0)
		sh->unset_oldpwd_s = 0;
	if (is_in_env(env, str) == SUCCESS)
		env_add(str, env);
}

static	void	ft_export_loop_valid(char *str, t_env *env,
										t_env *secret, t_sh *sh)
{
	if (!(ft_strchr(str, '=')))
	{
		check_in_env_and_add(str, secret, sh, 0);
	}
	else
	{
		check_in_env_and_add(str, env, sh, 1);
		check_in_env_and_add(str, secret, sh, 1);
	}
}

int				ft_export_loop(char **args, t_env *env, t_env *secret, t_sh *sh)
{
	int		i;
	int		flag_error;

	i = 1;
	flag_error = 0;
	while (args[i])
	{
		if (is_valid_env(args[i]) < 0)
		{
			flag_error = 1;
			print_error_in_export(args[i]);
		}
		else
		{
			ft_export_loop_valid(args[i], env, secret, sh);
		}
		i++;
	}
	return (flag_error);
}
