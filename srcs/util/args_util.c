/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 18:34:19 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/15 13:22:20 by kikeda           ###   ########.fr       */
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

char	*safe_strdup(const char *src)
{
	char *rtn;

	rtn = ft_strdup(src);
	if (rtn == NULL)
		no_mem();
	return (rtn);
}

char	*freeable_strjoin(char *s1, char *s2, int s1free, int s2free)
{
	char *new;

	new = ft_strjoin(s1, s2);
	if (s1free)
		free(s1);
	if (s2free)
		free(s2);
	if (new == NULL)
		no_mem();
	return (new);
}

void	dollar_trim(int trim, char **tmp)
{
	char	*new;

	if (!trim)
		return ;
	new = ft_strtrim(*tmp, " ");
	if (new)
	{
		no_mem();
	}
	free(*tmp);
	*tmp = new;
}
