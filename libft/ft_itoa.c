/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 21:17:15 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:34:37 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		calc_digit(int n)
{
	int ans;

	ans = 0;
	while (n)
	{
		n /= 10;
		ans++;
	}
	return (ans);
}

static void		put_itoa(char *str, unsigned int n, int digit)
{
	int i;

	i = 0;
	while (i < digit)
	{
		*(str + digit - 1 - i) = (n % 10) + '0';
		n /= 10;
		i++;
	}
}

char			*ft_itoa(int n)
{
	char	*rtn;
	int		digit;

	if (n == 0)
	{
		rtn = ft_calloc(1, 2);
		*rtn = '0';
		return (rtn);
	}
	rtn = ft_calloc(1, calc_digit(n) + (n < 0 ? 2 : 1));
	if (!rtn)
		return (NULL);
	*rtn = (n < 0 ? '-' : '\0');
	digit = calc_digit(n);
	if (n < 0)
		put_itoa(rtn + 1, (unsigned int)(n * -1), digit);
	else
		put_itoa(rtn, (unsigned int)n, digit);
	return (rtn);
}
