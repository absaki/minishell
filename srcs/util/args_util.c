/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kike <kike@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 18:34:19 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/03 15:13:02 by kike             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	free(cmd->cmds);
	free(cmd);
}

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
