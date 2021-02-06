/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 14:17:17 by kikeda            #+#    #+#             */
/*   Updated: 2020/07/08 18:52:17 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char *p;

	p = s;
	while (n)
	{
		n--;
		*p = (unsigned char)c;
		p++;
	}
	return (s);
}
