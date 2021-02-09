/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:12:38 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/06 22:27:10 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execvp(argv[0], argv);
		perror("cannot execute command");
		exit(1);
	}
	else
	{
		if (wait(&child_info) == -1)
			perror("wait");
	}
	return (child_info);
}
