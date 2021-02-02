/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 12:26:06 by kdoi              #+#    #+#             */
/*   Updated: 2020/07/11 16:14:21 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (len == 0)
		return (dst);
	if (!d && !s)
		return (NULL);
	if (s < d)
		while (len-- > 0)
			*(d + len) = *(s + len);
	else
		ft_memcpy(d, s, len);
	return (dst);
}
