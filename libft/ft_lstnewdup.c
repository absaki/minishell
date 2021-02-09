/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 22:40:44 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/09 23:16:00 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnewdup(void *content)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (new);
	new->content = ft_strdup(content);
	if (new->content == NULL)
		return (new);
	new->next = NULL;
	return (new);
}
