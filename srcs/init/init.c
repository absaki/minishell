/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:36:07 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/09 23:15:30 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		initenv(char **envp, t_env **env)
{
	int		count;
	t_env	*tmp;

	if (*envp == NULL)
		return (ERROR);
	*env = ft_lstnewdup(*envp);
	if (*env == NULL)
		return (ERROR);
	count = 1;
	while (*(envp + count))
	{
		tmp = ft_lstnewdup(*(envp + count++));
		if (tmp == NULL)
		{
			ft_lstclear(env, NULL);
			return (ERROR);
		}
		ft_lstadd_back(env, tmp);
	}
	return (SUCCESS);
}
