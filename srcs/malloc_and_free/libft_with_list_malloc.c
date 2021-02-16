/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_with_list_malloc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:38:40 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/16 18:16:03 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_and_list_malloc(const char *s1)
{
	char	*res;

	if (!(res = ft_strdup(s1)))
		exit_and_free("Failed to malloc. \n");
	add_list_malloc(res);
	return(res);
}
