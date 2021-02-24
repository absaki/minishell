/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 18:34:19 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/22 23:18:32 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		joinlast_onechr(char c, char **tmp)
{
	char	*new;
	int		i;
	int		newsize;

	i = 0;
	newsize = ft_strlen(*tmp) + 2;
	new = malloc(newsize);
	if (new == NULL)
		no_mem();
	while(*tmp != NULL && (*tmp)[i])
	{
		new[i] = (*tmp)[i];
		i++;
	}
	free(*tmp);
	new[i++] = c;
	new[i] = '\0';
	*tmp = new;
	return (1);
}
