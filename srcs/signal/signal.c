/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:16:01 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/20 23:33:18 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int status)
{
	(void)status;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd(DFL_PROMPT, STDERR);
		g_sig.sigint = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.sigint = 1;
	}
	return ;
}

void	sig_quit(int status)
{
	(void)status;
	if (g_sig.pid == 0)
	{
		return ;
	}
	else
	{
		ft_putstr_fd("Quit\n", STDERR);
		g_sig.sigquit = 1;
	}
	return ;
}
