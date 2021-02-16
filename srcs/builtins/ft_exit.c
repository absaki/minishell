/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:56:01 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/16 18:15:46 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_check_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void		ft_exit(t_sh *sh, char **args)
{
	// ここは、例のgithubではargsではなくcmdだが、便宜上argsにしておく
	sh->exit = 1;
	ft_putstr_fd("exit\n", STDERR);
	if (args[1] && args[2])
	{
		sh->ret = 1;
		ft_putendl_fd("bash: exit: too many arguments", STDERR);
	}
	else if (args[1] && ft_check_strisnum(args[1]) == 0)
	{
		sh->ret = 255;
		ft_putstr_fd("bash: exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (args[1])
		sh->ret = ft_atoi(args[1]);
	else
		sh->ret = 0;
}
