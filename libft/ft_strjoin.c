/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 18:08:11 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:36:41 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *p;

	if ((p = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1)))
	{
		ft_memcpy(p, s1, ft_strlen(s1));
		ft_memcpy(p + ft_strlen(s1), s2, ft_strlen(s2));
		return (p);
	}
	return (NULL);
}
