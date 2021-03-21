/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdread_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 23:39:50 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/21 14:20:31 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			sigint_reset(char **buf, int *pos, int *bufspace)
{
	free(*buf);
	*buf = 0;
	g_sig.sigint = 0;
	*pos = 0;
	*bufspace = 0;
}
