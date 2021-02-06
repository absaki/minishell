/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 18:20:45 by kikeda            #+#    #+#             */
/*   Updated: 2020/07/11 17:23:15 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*trim_begin(char const *s1, char const *set)
{
	int is_match;
	int i;

	while (*s1)
	{
		i = 0;
		is_match = 0;
		while (set[i])
		{
			is_match = (*s1 == set[i] ? 1 : 0);
			if (is_match)
				break ;
			i++;
		}
		if (is_match)
			s1++;
		else
			break ;
	}
	return ((char *)s1);
}

static int		calc_len(char const *s1, const char *set)
{
	int chk;
	int is_match;
	int i;

	chk = ft_strlen(s1) - 1;
	while (chk)
	{
		i = 0;
		is_match = 0;
		while (set[i])
		{
			is_match = (s1[chk] == set[i] ? 1 : 0);
			if (is_match)
				break ;
			i++;
		}
		if (is_match)
			chk--;
		else
			break ;
	}
	return (chk + 1);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*p;

	s1 = trim_begin(s1, set);
	if (*s1 == '\0')
		len = 0;
	else
		len = calc_len(s1, set);
	p = ft_calloc(1, len + 1);
	if (!p)
		return (NULL);
	if (len)
		ft_memcpy(p, s1, len);
	return (p);
}
