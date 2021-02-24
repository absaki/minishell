/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:56:01 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/24 14:00:49 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_will_overflow(int sign, unsigned long n, int next_digit)
{
	if (sign == 1)
	{
		if (n > (LONG_MAX / 10))
		{
			return (1);
		}
		if (n == (LONG_MAX / 10) && next_digit > (LONG_MAX % 10))
		{
			return (1);
		}
	}
	else if (sign == -1)
	{
		if (n > (LONG_MAX / 10))
		{
			return (1);
		}
		if (n == (LONG_MAX / 10) && next_digit > 8)
		{
			return (1);
		}
	}
	return (0);
}

static long		ft_strtonbr(const char *str, int sign)
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

static	long	ft_str_to_long(const char *str)
{
	int		sign;

	if (str == NULL)
		return (ERROR);
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	else
		sign = 1;
	return (ft_strtonbr(str, sign));
}

static	int		mod_by_256(char *str)
{
	long	mod;
	int		sign;

	mod = ft_str_to_long(str);
	sign = (mod < 0) ? -1 : 1;
	if (sign == -1)
	{
		if (ft_strcmp(str, "-9223372036854775808") == 0)
			return (0);
		else
			mod *= -1;
	}
	while (mod >= 256)
	{
		mod %= 256;
	}
	mod = (sign > 0) ? mod : (256 - mod);
	return ((int)mod);
}

void			ft_exit(t_sh *sh, char **args)
{
	sh->exit = 1;
	ft_putstr_fd("exit\n", STDERR);
	if (args[1] && args[2])
	{
		sh->ret = 1;
		ft_putendl_fd("bash: exit: too many arguments", STDERR);
	}
	else if (args[1] && ft_strcmp(args[1], "-1") == 0)
		sh->ret = 255;
	else if (args[1] && ft_str_to_long(args[1]) == -1)
	{
		sh->ret = 255;
		ft_putstr_fd("bash: exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (args[1])
		sh->ret = mod_by_256(args[1]);
	else
		sh->ret = 0;
}
