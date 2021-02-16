/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:06:13 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/16 18:15:23 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list			*g_list_malloc;

static	void	exit_and_print(char *s)
{
	int len;

	len = ft_strlen(s);
	write(1, s, len);
	exit(1);
}

void			exit_and_free(char *s)
{
	ft_lstclear(&g_list_malloc, free);
	exit_and_print(s);
}

void			add_list_malloc(void *ptr)
{
	t_list *new;

	if (g_list_malloc == NULL)
	{
		if (!(g_list_malloc = ft_lstnew(ptr)))
			exit_and_print("Failed to allocate g_list_malloc. \n");
	}
	else
	{
		if (!(new = ft_lstnew(ptr)))
			exit_and_free("Failed to allocate g_list_malloc. \n");
		ft_lstadd_front(&g_list_malloc, new);
	}
}

void			*malloc_with_list_malloc(size_t size)
{
	void *res;

	if (!(res = malloc(size)))
		exit_and_free("Failed to malloc. \n");
	if (res)
		add_list_malloc(res);
	return (res);
}
