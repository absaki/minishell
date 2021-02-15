/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 23:14:59 by kdoi              #+#    #+#             */
/*   Updated: 2020/12/18 01:17:37 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wc(char const *str, char delim)
{
	int wc;

	wc = 0;
	while (*str)
	{
		if (*str == delim)
			str++;
		else
		{
			wc++;
			while (*str && *str != delim)
				str++;
		}
	}
	return (wc);
}

static char	**teardown(char **res, int allocations)
{
	int i;

	i = 0;
	while (i < allocations)
		free(res[i]);
	free(res);
	return (NULL);
}

char		**create_strs(int wc, char const *s, char c)
{
	char	**res;
	int		word;
	int		i;

	if (!(res = malloc(sizeof(char *) * (wc + 1))))
		return (NULL);
	i = 0;
	while (*s && i < wc)
	{
		word = 0;
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			word++;
			s++;
		}
		if (!(*(res + i) = (char *)malloc(sizeof(char) * (word + 1))))
			return (teardown(res, i));
		(void)ft_strlcpy(*(res + i++), (s - word), word + 1);
	}
	*(res + i) = NULL;
	return (res);
}

char		**ft_split(char const *s, char c)
{
	char	**res;
	int		wc;

	if (s == NULL)
		return (NULL);
	wc = ft_wc(s, c);
	res = create_strs(wc, s, c);
	return (res);
}
