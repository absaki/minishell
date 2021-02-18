/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 22:48:08 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/12 23:07:31 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cut_arg_redirection(char ***argv, int tail)
{
	int		i;
	int		oldsize;
	char	**new;

	i = 0;
	oldsize = strlistlen(*argv);
	if ((new = (char **)malloc(sizeof(char *) * oldsize)) == 0)
		exit(-1);
	while (i < tail)
	{
		if ((new[i] = ft_strdup((*argv)[i])) == 0)
			exit(-1);
		free((*argv)[i]);
		i++;
	}
	while (i + 2 < oldsize)
	{
		if ((new[i] = ft_strdup((*argv)[i + 2])) == 0)
			exit(-1);
		free((*argv)[i + 2]);
		i++;
	}
	new[i] = 0;
	free(*argv);
	return (new);
}

int		redirection_read(char ***argv, int i)
{
	int fd;

	if (ft_strncmp((*argv)[i], "<", 2) == 0 && (*argv)[i + 1])
	{
		if ((fd = open((*argv)[i + 1], O_RDONLY,
			S_IRWXU | S_IRGRP)) != -1)
			dup2(fd, 0);
		else
		{
			ft_putstr_fd("No such file or directory\n", 2);
			exit(-1);
		}
		*argv = cut_arg_redirection(argv, i);
		return (1);
	}
	return (0);
}

int		redirection_append(char ***argv, int i)
{
	int fd;

	if (ft_strncmp((*argv)[i], ">>", 2) == 0 && (*argv)[i + 1])
	{
		if ((fd = open((*argv)[i + 1], O_APPEND | O_CREAT | O_WRONLY,
			S_IRWXU | S_IRGRP)) != -1)
			dup2(fd, 1);
		else
		{
			ft_putstr_fd("No such file or directory\n", 2);
			exit(-1);
		}
		*argv = cut_arg_redirection(argv, i);
		return (1);
	}
	return (0);
}

int		redirection_write(char ***argv, int i)
{
	int		fd;

	if (ft_strncmp((*argv)[i], ">", 2) == 0 && (*argv)[i + 1])
	{
		if ((fd = open((*argv)[i + 1], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRWXU | S_IRGRP)) != -1)
			dup2(fd, 1);
		else
		{
			ft_putstr_fd("No such file or directory\n", 2);
			exit(-1);
		}
		*argv = cut_arg_redirection(argv, i);
		return (1);
	}
	return (0);
}
