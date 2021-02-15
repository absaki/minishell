/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 23:48:44 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:37:16 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int i;

	i = ft_strlen(s) + 1;
	while (i--)
	{
		if (*(s + i) == (char)c)
			return ((char *)(s + i));
	}
	return (0);
}
