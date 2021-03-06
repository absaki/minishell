/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:03:04 by kdoi              #+#    #+#             */
/*   Updated: 2021/03/06 17:03:35 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r' || c == ' ' ? 1 : 0);
}

int		ft_will_overflow(int sign, unsigned long n, int next_digit)
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
