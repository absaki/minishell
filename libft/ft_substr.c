/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 17:25:09 by kikeda            #+#    #+#             */
/*   Updated: 2020/07/11 17:41:52 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		max;
	char	*p;

	if (start > ft_strlen(s))
	{
		p = ft_calloc(1, 1);
		return (p);
	}
	max = (ft_strlen(s + start) > len ? len : ft_strlen(s + start));
	if ((p = ft_calloc(sizeof(char), max + 1)))
	{
		ft_strlcpy(p, s + start, max + 1);
		return (p);
	}
	return (NULL);
}
