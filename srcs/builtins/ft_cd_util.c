/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 23:49:26 by kdoi              #+#    #+#             */
/*   Updated: 2021/03/06 18:47:34 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_error_and_set_errno(char *str)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

char		*check_env_value(char *arg, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_val;

	if (arg[0] == 0)
		return (NULL);
	env_val = ft_strdup("");
	while (env && env->vl)
	{
		get_env_name(env_name, env->vl);
		if (ft_strcmp(arg, env_name) == 0)
		{
			ft_free_and_del(env_val);
			env_val = env_value(env->vl);
			return (env_val);
		}
		env = env->next;
	}
	return (NULL);
}
