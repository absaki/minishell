/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 12:42:48 by kdoi              #+#    #+#             */
/*   Updated: 2020/12/19 16:59:56 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t catsize;
	size_t dstlen;
	size_t srclen;
	size_t i;

	catsize = 0;
	while (dst[catsize])
		catsize++;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = 0;
	while (i < srclen && dstlen + i + 1 < dstsize)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (catsize + srclen);
}
