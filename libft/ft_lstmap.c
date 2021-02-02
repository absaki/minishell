/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 00:00:48 by kdoi              #+#    #+#             */
/*   Updated: 2020/07/11 16:52:39 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_head;
	t_list *current;

	if (lst == NULL || f == NULL)
		return (NULL);
	if ((new_head = ft_lstnew(f(lst->content))) == NULL)
		return (NULL);
	current = new_head;
	while (lst->next)
	{
		lst = lst->next;
		if ((current->next = ft_lstnew(f(lst->content))) == NULL)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		current = current->next;
	}
	return (new_head);
}
