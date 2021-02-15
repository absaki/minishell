/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 23:21:58 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:35:50 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int i;

	if (!dest)
		return (NULL);
	i = 0;
	if (dest <= src)
	{
		while (i < n)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	else if (src < dest)
	{
		while (i < n)
		{
			*(unsigned char *)(dest + n - 1 - i) =
				*(unsigned char *)(src + n - 1 - i);
			i++;
		}
	}
	return (dest);
}
