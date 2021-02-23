/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 01:43:53 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/21 19:28:46 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_args_in_unset(char *str, t_sh *sh)
{
	if (ft_strcmp(str, "PWD") == 0)
	{
		sh->unset_pwd = 1;
		sh->unset_pwd_s = 1;
	}
	if (ft_strcmp(str, "OLDPWD") == 0)
	{
		sh->unset_oldpwd = 1;
		sh->unset_oldpwd_s = 1;
	}
}

void	print_error_in_unset(char *arg)
{
	ft_putstr_fd("bash: unset: `", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putendl_fd("': not a valid identifier", STDERR);
}
