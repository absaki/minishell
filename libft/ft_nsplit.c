/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 15:45:53 by kikeda            #+#    #+#             */
/*   Updated: 2020/12/16 17:34:21 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *s, char c)
{
	unsigned int	i;
	int				ans;
	int				is_match;

	i = 0;
	ans = 0;
	is_match = 1;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && is_match)
		{
			is_match = 0;
			ans++;
		}
		else if (s[i] == c)
		{
			is_match = 1;
		}
		i++;
	}
	return (ans);
}

static int		ft_strlen_c(const char *s, char c)
{
	int n;

	n = 0;
	while (*s != c && *s)
	{
		s++;
		n++;
	}
	return (n);
}

static char		*arr_strcpy(char const *s, char c)
{
	char *rtn;

	rtn = (char *)ft_calloc(1, ft_strlen_c(s, c) + 1);
	if (rtn == NULL)
		return (rtn);
	ft_memcpy(rtn, s, ft_strlen_c(s, c));
	return (rtn);
}

static char		**do_split(char const *s, char c, int num)
{
	char	**rtn;
	int		i;

	rtn = (char **)malloc(sizeof(char *) * ((num) + 1));
	rtn[num] = NULL;
	i = 0;
	while (i < num && rtn)
	{
		rtn[i] = arr_strcpy(s, c);
		if (!rtn[i])
		{
			while (--i >= 0)
				free(rtn[i]);
			free(rtn);
			return (NULL);
		}
		if (i == num - 1)
			break ;
		while (*s != c)
			s++;
		while (*s == c)
			s++;
		i++;
	}
	return (rtn);
}

int				ft_nsplit(char const *s, char ***output, char c)
{
	char	c_str[2];
	int		words;
	char	**ans;
	char	*trimed;

	c_str[0] = c;
	c_str[1] = '\0';
	trimed = ft_strtrim(s, c_str);
	if (trimed == 0)
		return (-1);
	words = count_words(trimed, c);
	ans = do_split(trimed, c, words);
	free(trimed);
	*output = ans;
	return (words);
}
