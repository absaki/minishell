/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_rd_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:42:11 by kike              #+#    #+#             */
/*   Updated: 2021/03/14 18:43:27 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	openzero(t_redirection *rd)
{
	int fd;

	fd = open(rd->file, O_RDONLY);
	if (fd != -1)
	{
		dup2(fd, 0);
		close(fd);
		return (SUCCESS);
	}
	ft_putstr_fd("No such file or directory\n", 2);
	return (ERROR);
}

static int	openone(t_redirection *rd)
{
	int fd;
	int permisiion;

	if (rd->f_append)
		permisiion = O_APPEND | O_CREAT | O_WRONLY;
	else
		permisiion = O_CREAT | O_WRONLY | O_TRUNC;
	if ((fd = open(rd->file, permisiion,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
	{
		dup2(fd, 1);
		close(fd);
		return (SUCCESS);
	}
	ft_putstr_fd("No such file or directory\n", 2);
	return (ERROR);
}

static int	opentwo(t_redirection *rd)
{
	int fd;
	int permisiion;

	if (rd->f_append)
		permisiion = O_APPEND | O_CREAT | O_WRONLY;
	else
		permisiion = O_CREAT | O_WRONLY | O_TRUNC;
	if ((fd = open(rd->file, permisiion,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
	{
		dup2(fd, 2);
		close(fd);
		return (SUCCESS);
	}
	ft_putstr_fd("No such file or directory\n", 2);
	return (ERROR);
}

int			set_fd(t_sh *sh)
{
	t_redirection	*rd;
	t_rdlist		*list;
	int				open_result;

	list = sh->rdlist;
	while (list)
	{
		rd = list->content;
		if (rd->fd == 0)
			open_result = openzero(rd);
		else if (rd->fd == 1)
			open_result = openone(rd);
		else if (rd->fd == 2)
			open_result = opentwo(rd);
		else
			break ;
		if (open_result == ERROR)
			return (ERROR);
		list = list->next;
	}
	return (SUCCESS);
}
