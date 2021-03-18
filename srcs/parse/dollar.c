/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:16:53 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/18 13:52:53 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			replace_dollar(char **cmdl, t_sh *sh)
{
	char	*old;
	char	*new;
	int		i;

	i = 0;
	old = *cmdl;
	new = my_malloc(sizeof(char));
	new[0] = '\0';
	while (old[i])
	{
		if (old[i] == '\'')
		{
			i += joinlast_onechr(old[i], &new);
			while (old[i] != '\'')
				i += joinlast_onechr(old[i], &new);
			i += joinlast_onechr(old[i], &new);
		}
		else if (old[i] == '$')
			i += dollar(&(old[i]), sh, &new);
		else
			i += joinlast_onechr(old[i], &new);
	}
	free(old);
	*cmdl = new;
}
