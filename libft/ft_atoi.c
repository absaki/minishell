/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 16:19:53 by kdoi              #+#    #+#             */
/*   Updated: 2020/07/11 16:09:55 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	ft_will_overflow(unsigned long n, int next_digit)
{
	if (n > (LONG_MAX) / 10)
		return (1);
	if (n == (LONG_MAX / 10) && next_digit > (LONG_MAX % 10))
		return (1);
	return (0);
}

static int	ft_strtonbr(const char *str, int sign)
{
	unsigned long	n;
	int				d;

	n = 0;
	while (ft_isdigit(*str))
	{
		d = *str - '0';
		if (ft_will_overflow(n, d))
			return (sign == 1 ? (int)LONG_MAX : (int)LONG_MIN);
		n = n * 10 + d;
		str++;
	}
	return ((int)n * sign);
}

int			ft_atoi(const char *str)
{
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	return (ft_strtonbr(str, sign));
}
