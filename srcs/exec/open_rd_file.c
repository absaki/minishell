/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_rd_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:42:11 by kike              #+#    #+#             */
/*   Updated: 2021/03/12 21:12:55 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int open0(t_redirection *rd)
{
    int fd;

    if ((fd = open(rd->file, O_RDONLY) != -1))
        {
		dup2(fd, 0);
        return (SUCCESS);
        }
    ft_putstr_fd("No such file or directory\n", 2);
    return (ERROR);    
}

static int open1(t_redirection *rd)
{
    int fd;
    int permisiion;

    if (rd->f_append)
        permisiion = O_APPEND | O_CREAT | O_WRONLY;
    else
        permisiion = O_CREAT | O_WRONLY | O_TRUNC;
    if ((fd = open(rd->file, permisiion, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
        {
		dup2(fd, 1);
        return (SUCCESS);
        }
    ft_putstr_fd("No such file or directory\n", 2);
    return (ERROR);    
}

static int open2(t_redirection *rd)
{
    int fd;
    int permisiion;

    if (rd->f_append)
        permisiion = O_APPEND | O_CREAT | O_WRONLY;
    else
        permisiion = O_CREAT | O_WRONLY | O_TRUNC;
    if ((fd = open(rd->file, permisiion, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
        {
		dup2(fd, 2);
        return (SUCCESS);
        }
    ft_putstr_fd("No such file or directory\n", 2);
    return (ERROR);    
}

int         set_fd(t_sh *sh)
{
	t_redirection *rd;
    int open_result;

	while(sh->rdlist)
	{
		rd = sh->rdlist->content;
		if(rd->fd == 0)
		    open_result = open0(rd);
		else if(rd->fd == 1)
		    open_result = open1(rd);
		else if(rd->fd == 2)
		    open_result = open2(rd);
		else
			break;
        if(open_result == ERROR)
            return (ERROR);
		sh->rdlist = sh->rdlist->next;
	}
    return (SUCCESS);
}
