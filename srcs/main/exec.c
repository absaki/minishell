/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:12:38 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/12 22:47:42 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd(char ***argv)
{
	int i;

	i = 0;
	while ((*argv)[i])
	{
		i -= redirection_write(argv, i);
		i -= redirection_append(argv, i);
		i -= redirection_read(argv, i);
		i++;
	}
}

void	exec_child(char **argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_fd(&argv);
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
