/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:48:31 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/14 23:04:25 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				substrend(char **str, int rstart, int rend)
{
	char	*new;
	int		oldlen;
	int		i;
	int		j;

	oldlen = ft_strlen(*str);
	if (rend < rstart || oldlen <= rstart || oldlen <= rend)
		return (ERROR);
	if ((new = malloc(oldlen - (rend - rstart))) == NULL)
		no_mem();
	i = 0;
	j = 0;
	while ((*str)[i] && i < rstart)
		new[j++] = (*str)[i++];
	if (i == rstart)
		i = rend + 1;
	while ((*str)[i])
		new[j++] = (*str)[i++];
	new[j] = '\0';
	free(*str);
	*str = new;
	return (SUCCESS);
}

void			rd_free(t_redirection *rd)
{
	free(rd->file);
	free(rd);
}

/*
** REDIRECTION INT
** 0:   NOP
** 1:   STDIN
** 2:   STDOUT WRITE
** 3:   STDERR WRITE
** 4:   STDOUT APPEND
** 5:   STDERR APPEND
*/

int				is_nonum_rd(char **str, int i)
{
	if (!ft_strncmp(">>", &(*str)[i], 2) && !substrend(str, i, i + 1))
		return (4);
	if (!ft_strncmp(">", &(*str)[i], 1) && !substrend(str, i, i))
		return (2);
	if (!ft_strncmp("<", &(*str)[i], 1) && !substrend(str, i, i))
		return (1);
	return (0);
}

int				is_num_rd(char **str, int i)
{
	if (!ft_strncmp("1>>", &(*str)[i], 3) && !substrend(str, i, i + 2))
		return (4);
	if (!ft_strncmp("2>>", &(*str)[i], 3) && !substrend(str, i, i + 2))
		return (5);
	if (!ft_strncmp("1>", &(*str)[i], 2) && !substrend(str, i, i + 1))
		return (2);
	if (!ft_strncmp("2>", &(*str)[i], 2) && !substrend(str, i, i + 1))
		return (3);
	if (!ft_strncmp("0<", &(*str)[i], 2) && !substrend(str, i, i + 1))
		return (1);
	return (0);
}

t_redirection	*t_rd_dup(char *rdfile, int mode)
{
	t_redirection *new;

	if ((new = malloc(sizeof(t_redirection))) == NULL)
		no_mem();
	if (mode == 1)
		new->fd = 0;
	else if (mode == 2 || mode == 4)
		new->fd = 1;
	else if (mode == 3 || mode == 5)
		new->fd = 2;
	if (mode == 1 || mode == 2 || mode == 3)
		new->f_append = 0;
	else if (mode == 4 || mode == 5)
		new->f_append = 1;
	if (rdfile)
		new->file = rdfile;
	return (new);
}
