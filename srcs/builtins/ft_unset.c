/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:24:44 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/24 13:50:17 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	sizenv(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static	void	search_env_and_secret(char *str, t_env *env,
										t_env *secret, t_sh *sh)
{
	while (env && env->next)
	{
		if (ft_strncmp(str, env->next->vl,
			sizenv(env->next->vl)) == 0)
		{
			check_args_in_unset(str, sh);
			env->next = env->next->next;
		}
		env = env->next;
	}
	while (secret && secret->next)
	{
		if (ft_strncmp(str, secret->next->vl,
			sizenv(secret->next->vl)) == 0)
		{
			check_args_in_unset(str, sh);
			secret->next = secret->next->next;
		}
		secret = secret->next;
	}
}

static void		ft_unset_loop(char **args, t_sh *sh, int *flag_error)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (is_valid_env(args[i]) < 0)
		{
			*flag_error = 1;
			print_error_in_unset(args[i]);
		}
		else if (ft_strncmp(args[i], sh->env->vl, sizenv(sh->env->vl)) == 0)
		{
			check_args_in_unset(args[i], sh);
			sh->env = (sh->env->next) ? sh->env->next : sh->env;
		}
		else if (ft_strncmp(args[i], sh->senv->vl, sizenv(sh->senv->vl)) == 0)
		{
			check_args_in_unset(args[i], sh);
			sh->senv = (sh->senv->next) ? sh->senv->next : sh->env;
		}
		else
			search_env_and_secret(args[i], sh->env, sh->senv, sh);
	}
}

int				ft_unset(char **args, t_sh *sh)
{
	int		*flag_error;
	int		temp;

	if (!(args[1]))
		return (SUCCESS);
	temp = 0;
	flag_error = &temp;
	ft_unset_loop(args, sh, flag_error);
	if (*flag_error == 1)
		return (ERROR);
	else
		return (SUCCESS);
}
