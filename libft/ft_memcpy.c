/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:52:27 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:35:41 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*d;

	if (!dst)
		return (NULL);
	d = dst;
	while (n--)
	{
		*(unsigned char *)d++ = *(unsigned char *)src++;
	}
	return (dst);
}
