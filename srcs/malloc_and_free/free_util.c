/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 18:06:39 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/06 17:20:50 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
