/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 18:06:39 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/17 01:38:54 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list_malloc(void)
{
	ft_lstclear(&g_list_malloc, free);
}

void	free_tda(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			ft_free_and_del(tab[i]);
		i++;
	}
	if (tab)
		ft_free_and_del(tab);
}
