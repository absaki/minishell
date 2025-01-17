/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 12:02:21 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:36:35 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char *p;

	if ((p = ft_calloc(1, ft_strlen(s) + 1)))
	{
		ft_memcpy(p, s, ft_strlen(s) + 1);
		return (p);
	}
	return (NULL);
}
