/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 10:22:09 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:37:12 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int				is_match;
	unsigned int	i;
	char			*start;

	start = (char *)big;
	is_match = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (*start)
	{
		i = 0;
		while ((unsigned int)(start - big) + i < len)
		{
			if (little[i] == '\0')
				break ;
			is_match = (start[i] == little[i] ? 1 : 0);
			i++;
			if (is_match == 0)
				break ;
		}
		if (is_match && little[i] == '\0')
			return ((char *)start);
		start++;
	}
	return (0);
}
