/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:56:01 by kdoi              #+#    #+#             */
/*   Updated: 2021/03/13 14:50:07 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_strtonbr(const char *str, int sign)
{
	unsigned long	n;
	int				d;

	n = 0;
	while (ft_isdigit(*str))
	{
		d = *str - '0';
		if (ft_will_overflow(sign, n, d))
			return (-1);
		n = n * 10 + d;
		str++;
	}
	return (n * sign);
}

long		ft_atol(const char *str)
{
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	return (ft_strtonbr(str, sign));
}

int			ft_isdigits(char *s)
{
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
		s++;
	while (ft_isspace(*s))
		s++;
	if (*s == '\0')
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s) && !ft_isspace(*s))
			return (0);
		s++;
	}
	return (1);
}

int			get_status(char *str)
{
	long	status;

	status = ft_atol(str);
	if (status == -1 && ft_strcmp(str, "-1") != 0)
		status = 255;
	return ((int)status);
}

void		ft_exit(t_sh *sh, char **args)
{
	sh->exit = 1;
	ft_putstr_fd("exit\n", STDERR);
	if (args[1] && args[2])
	{
		sh->ret = 1;
		ft_putendl_fd("bash: exit: too many arguments", STDERR);
	}
	else if (args[1])
	{
		if (ft_isdigits(args[1]))
			sh->ret = get_status(args[1]);
		else
			sh->ret = 255;
	}
	else
		sh->ret = g_sig.status;
	if (sh->ret == 255)
		ft_putendl_fd("minishell: exit: numeric argument required", STDERR);
	exit(sh->ret);
}
