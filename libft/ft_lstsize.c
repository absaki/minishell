/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 23:03:25 by kdoi              #+#    #+#             */
/*   Updated: 2020/07/11 16:14:07 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	if (lst == NULL)
	{
		return (0);
	}
	count = 1;
	while (lst->next != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
