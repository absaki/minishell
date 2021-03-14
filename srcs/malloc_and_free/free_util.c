/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 18:06:39 by kdoi              #+#    #+#             */
/*   Updated: 2021/03/14 22:42:22 by kikeda           ###   ########.fr       */
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

void	no_mem(void)
{
	exit(1);
}

void	*my_malloc(size_t size)
{
	void	*rtn;

	rtn = malloc(size);
	if (rtn == NULL)
		no_mem();
	return (rtn);
}
