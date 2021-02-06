/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 23:40:32 by kikeda            #+#    #+#             */
/*   Updated: 2020/07/08 17:48:59 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	unsigned long long	ans;
	int					is_minus;

	ans = 0;
	while ((0 < *nptr && *nptr <= 26) || *nptr == ' ')
		nptr++;
	is_minus = (*nptr == '-' ? 1 : 0);
	nptr += (*nptr == '-' || *nptr == '+' ? 1 : 0);
	while ('0' <= *nptr && *nptr <= '9')
	{
		if ('0' <= *nptr && *nptr <= '9')
		{
			ans *= 10;
			ans += *nptr - '0';
		}
		nptr++;
	}
	return (ans * (is_minus ? -1 : 1));
}
