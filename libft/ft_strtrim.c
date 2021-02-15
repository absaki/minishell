/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 23:05:25 by kdoi              #+#    #+#             */
/*   Updated: 2020/07/11 16:42:35 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	set_char_table(int table[256], unsigned char *set)
{
	int i;

	i = 0;
	while (i < 256)
		table[i++] = 0;
	while (*set)
		table[*set++] = 1;
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		table[256];
	int		start;
	int		end;
	int		len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	set_char_table(table, (unsigned char *)set);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (start <= end && table[(unsigned char)s1[start]])
		start++;
	while (end >= start && table[(unsigned char)s1[end]])
		end--;
	len = end - start + 1;
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	(void)ft_strlcpy(res, s1 + start, len + 1);
	return (res);
}
