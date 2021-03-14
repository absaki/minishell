/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:11:18 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/14 22:40:01 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(t_sh *sh)
{
	char	*lvlval;
	int		oldlvl;
	char	*new;

	lvlval = get_env_value("SHLVL", sh->env);
	if (lvlval[0] == '\0')
	{
		env_add("SHLVL=1", sh->env);
		return ;
	}
	oldlvl = ft_atoi(lvlval);
	free(lvlval);
	if (1 <= oldlvl && oldlvl < 998)
		lvlval = ft_itoa(oldlvl + 1);
	else
		lvlval = ft_itoa(1);
	new = ft_strjoin("SHLVL=", lvlval);
	free(lvlval);
	is_in_env(sh->env, new);
	free(new);
}
