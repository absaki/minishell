/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:12:38 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/11 21:24:23 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cut_arg_redirection(char ***argv, int tail)
{
	int		i;
	char	**new;

	i = 0;
	if ((new = (char **)malloc(sizeof(char *) * tail)) == 0)
		exit(-1);
	while (i < tail)
	{
		if ((new[i] = ft_strdup((*argv)[i])) == 0)
			exit(-1);
		free((*argv)[i]);
		i++;
	}
	new[i] = 0;
	free(*argv);
	return (new);
}

void	set_outfd(char ***argv)
{
	int fd;
	int i;

	i = 0;
	while ((*argv)[i])
	{
		if (ft_strncmp((*argv)[i], ">", 2) == 0)
		{
			if ((fd = open((*argv)[i + 1], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRWXU | S_IRGRP)) != -1)
				dup2(fd, 1);
			else
				perror("can not open the file.");
			*argv = cut_arg_redirection(argv, i);
			break ;
		}
		i++;
	}
}

void	exec_child(char **argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_outfd(&argv);
	execvp(argv[0], argv);
	perror("cannot execute command");
	exit(1);
}

int		execute(char *argv[])
{
	int pid;
	int child_info;

	child_info = -1;
	if (argv[0] == NULL)
		return (0);
	if ((pid = fork()) == -1)
		perror("fork");
	else if (pid == 0)
		exec_child(argv);
	else
	{
		if (wait(&child_info) == -1)
			perror("wait");
	}
	return (child_info);
}
