/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:36:35 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/07 23:35:16 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_env(char **args, t_env *env)
{
	if (args[1])
	{
		ft_putstr_fd("env: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		return(ERROR);//bashで確認する限り、statusの出力は127になっているが今回は引数やオプションは対象外なのでこれでいいのか？
	}
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value, 1);//環境変数_の出力内容を確認
	return (SUCCESS);
}
