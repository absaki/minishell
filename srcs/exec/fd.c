/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:37:59 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/14 18:38:21 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		buk_fds(int fds[3])
{
	fds[0] = dup(0);
	fds[1] = dup(1);
	fds[2] = dup(2);
	if (fds[0] && fds[1] && fds[2])
		return (SUCCESS);
	else
		return (ERROR);
}

int		reset_fds(int fds[3])
{
	if (
		dup2(fds[0], 0) != -1 && dup2(fds[1], 1) != -1 && dup2(fds[2], 2)
		!= -1 && close(fds[0]) != -1
		&& close(fds[1]) != -1 && close(fds[2]) != -1)
	{
		return (SUCCESS);
	}
	return (ERROR);
}
