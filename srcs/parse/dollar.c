/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:16:53 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/20 23:14:17 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		replace_one_block(char *old, int *i, char **new, t_sh *sh)
{
	if (old[*i] == '\\' && old[*i + 1])
	{
		*i += joinlast_onechr(old[*i], new)
		+ joinlast_onechr(old[*i + 1], new);
		return (1);
	}
	else if (old[*i] == '\'')
	{
		*i += joinlast_onechr(old[*i], new);
		while (old[*i] != '\'')
			*i += joinlast_onechr(old[*i], new);
		*i += joinlast_onechr(old[*i], new);
		return (1);
	}
	else if (old[*i] == '$')
	{
		*i += dollar(&(old[*i]), sh, new);
		return (1);
	}
	return (0);
}

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
		if (!replace_one_block(old, &i, &new, sh))
			i += joinlast_onechr(old[i], &new);
	}
	free(old);
	*cmdl = new;
}
