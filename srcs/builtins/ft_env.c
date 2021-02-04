/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:36:35 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/04 22:01:59 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, 1);//環境変数_の出力内容を確認
	return (SUCCESS);
}
