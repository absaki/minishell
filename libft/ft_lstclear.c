/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 00:22:46 by kdoi              #+#    #+#             */
/*   Updated: 2020/07/11 16:53:51 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *p;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		p = (*lst)->next;
		if (del != NULL && (*lst)->content != NULL)
			(*del)((*lst)->content);
		free(*lst);
		*lst = p;
	}
}
