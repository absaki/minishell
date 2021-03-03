/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 23:49:26 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/27 23:50:37 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_error_and_set_errno(char *str)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
}
