/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 21:24:42 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:35:13 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *p;
	t_list *start;

	if (!f)
		return (NULL);
	start = NULL;
	while (lst)
	{
		p = ft_lstnew((*f)(lst->content));
		if (!p)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		if (!start)
			start = p;
		else
			ft_lstadd_back(&start, p);
		lst = lst->next;
	}
	return (start);
}
