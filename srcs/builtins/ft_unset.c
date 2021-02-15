/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:24:44 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/07 23:34:41 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		print_error_in_unset(char *arg)
{
	ft_putstr_fd("bash: unset: `", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd("': not a valid identifier", STDERR);
}

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static	void	search_env_and_secret(char **args,
	t_env *env, t_env *secret, int i)
{
	while (env && env->next)
	{
		if (ft_strncmp(args[i], env->next->value,
			env_size(env->next->value)) == 0)
			env->next = env->next->next;
		env = env->next;
	}
	while (secret && secret->next)
	{
		if (ft_strncmp(args[i], secret->next->value,
			env_size(secret->next->value)) == 0)
			secret->next = secret->next->next;
		secret = secret->next;
	}
}

static int		ft_unset_loop(char **args, t_env *env, t_env *secret)
{
	int		i;
	int		flag_error;

	flag_error = 0;
	i = 1;
	while (args[i])
	{
		if (is_valid_env(args[i]) < 0)
		{
			flag_error = 1;
			print_error_in_unset(args[i++]);
			continue;
		}
		if (ft_strncmp(args[i], env->value, env_size(env->value)) == 0)
			env = (env->next) ? env->next : env;//memory leak要確認
		if (ft_strncmp(args[i], secret->value, env_size(secret->value)) == 0)
		{
			secret = (secret->next) ? secret->next : env;//memory leak要確認
			i++;
			continue;
		}
		search_env_and_secret(args, env, secret, i);
		i++;
	}
	return (flag_error);
}

int				ft_unset(char **args, t_env *env, t_env *secret)
{
	int		flag_error;

	if (!(args[1]))
		return (SUCCESS);
	flag_error = ft_unset_loop(args, env, secret);
	if (flag_error == 1)
		return (ERROR);
	else
		return (SUCCESS);
}
