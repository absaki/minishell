/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 11:23:19 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:34:11 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*p;
	unsigned int	i;

	if (nmemb * size == 0)
	{
		p = malloc(1);
		*(char *)p = '\0';
		return (p);
	}
	i = 0;
	p = malloc(nmemb * size);
	if (p)
	{
		while (i < nmemb * size)
			*(char *)(p + i++) = '\0';
		return (p);
	}
	return (NULL);
}
