/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 23:28:01 by kdoi              #+#    #+#             */
/*   Updated: 2020/07/11 16:15:04 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	if (!(new = ft_strdup(s)))
		return (NULL);
	if (f == NULL)
		return (new);
	i = -1;
	while (new[++i])
		new[i] = f(i, s[i]);
	return (new);
}
