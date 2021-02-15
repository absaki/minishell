/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 10:55:34 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:37:03 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*rtn;

	i = 0;
	rtn = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!rtn)
		return (NULL);
	while (i < ft_strlen(s))
	{
		rtn[i] = (*f)(i, s[i]);
		i++;
	}
	return (rtn);
}
