/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kike <kike@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 18:34:19 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/03 22:09:59 by kike             ###   ########.fr       */
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
	int		tmpsize;

	tmpsize = ft_strlen(*tmp);
	if ((new = malloc(sizeof(char) * (tmpsize + 2))) == NULL)
		no_mem();
	ft_memcpy(new, *tmp, ft_strlen(*tmp));
	free(*tmp);
	new[tmpsize] = c;
	new[tmpsize + 1] = '\0';
	*tmp = new;
	return (1);
}
