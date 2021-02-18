/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 23:18:00 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:36:12 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		write_num(unsigned int n, int fd)
{
	char num;

	if (n <= 9)
	{
		num = '0' + n;
		write(fd, &num, 1);
	}
	else
	{
		write_num(n / 10, fd);
		write_num(n % 10, fd);
	}
}

void			ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		write_num((unsigned int)(n * -1), fd);
	}
	else
		write_num((unsigned int)n, fd);
}
