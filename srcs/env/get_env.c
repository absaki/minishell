/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:27:41 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/27 23:38:12 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int		is_valid_env(const char *str)
{
	int		i;

	if (str[0] == '-' || str[0] == '=' || ('0' <= str[0] && str[0] <= '9'))
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_' && str[i] != '\\')
			return (-1);
		i++;
	}
	if (str[i] != '=')
		return (2);
	return (1);
}

int		env_value_len(const char *env)
{
	int		i;
	int		size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

char	*env_value(char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	size_alloc = env_value_len(env) + 1;
	if (!(env_value = malloc(sizeof(char) * size_alloc)))
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*get_env_value(char *arg, t_env *env)
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
	return (env_val);
}
