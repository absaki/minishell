/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_empty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:10:09 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/18 17:02:50 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_str(char *s, char c)
{
	int i;
	int size;

	size = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			size++;
		i++;
	}
	return (size);
}

static int		store_str(char *src, char **dst, int pos, char c)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = pos;
	while (src[i] && src[i] != c)
		i++;
	len = i - pos;
	if ((new = malloc((len) + 1)) == NULL)
		return (0);
	i = pos;
	j = 0;
	while (j < len && src[i] && src[i] != c)
		new[j++] = src[i++];
	new[j] = '\0';
	*dst = new;
	return (len);
}

char			**ft_split_empty(char *s, char c)
{
	char	**rtn;
	int		i;
	int		strnum;
	int		len;

	len = count_str(s, c);
	rtn = malloc(sizeof(char *) * (len + 1));
	if (rtn == NULL)
		return (rtn);
	i = 0;
	strnum = 0;
	while (strnum < len)
	{
		if (s[i] == c)
			i++;
		if (ft_strlen(&(s[i])) == 0 && (rtn[strnum++] = ft_strdup("")))
			break ;
		i += store_str(s, &(rtn[strnum]), i, c);
		strnum++;
	}
	rtn[strnum] = NULL;
	return (rtn);
}
