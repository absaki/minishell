/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:14:24 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/24 13:50:08 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		get_len_of_tda(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static void		write_with_dquote(char *str)
{
	int		i;

	ft_putstr_fd("declare -x ", 1);
	i = 0;
	while (str[i] != '=' && str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	if (str[i] == '=')
	{
		write(1, &str[i++], 1);
		write(1, "\"", 1);
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
		}
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

static	void	print_sorted_env_loop(t_sh *sh, char **tab, int i)
{
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "PWD", 3) == 0)
		{
			if (sh->unset_pwd_s == 0)
				write_with_dquote(tab[i]);
		}
		else if (ft_strncmp(tab[i], "OLDPWD", 6) == 0)
		{
			if (sh->unset_oldpwd_s == 0)
				write_with_dquote(tab[i]);
		}
		else
			write_with_dquote(tab[i]);
		i++;
	}
}

static	void	print_sorted_env(t_env *env, t_sh *sh)
{
	char	**tab;
	char	*str_env;

	str_env = convert_env_to_str(env);
	tab = ft_split(str_env, '\n');
	ft_free_and_del(str_env);
	sort_env_by_asc(tab, get_len_of_tda(tab));
	print_sorted_env_loop(sh, tab, 0);
	free_tda(tab);
}

int				ft_export(char **args, t_env *env, t_env *secret, t_sh *sh)
{
	int		flag_error;

	flag_error = 0;
	if (!args[1])
	{
		print_sorted_env(secret, sh);
		return (SUCCESS);
	}
	else
		flag_error = ft_export_loop(args, env, secret, sh);
	if (flag_error == 1)
		return (ERROR);
	else
		return (SUCCESS);
}
