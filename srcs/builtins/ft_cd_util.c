/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 23:49:26 by kdoi              #+#    #+#             */
/*   Updated: 2021/03/13 19:50:46 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->vl, var, len) == 0)
		{
			s_alloc = ft_strlen(env->vl) - len;
			if (!(oldpwd = malloc(sizeof(char) * s_alloc + 1)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->vl[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->vl[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

int			update_cwd(t_sh *sh)
{
	char	temp_cwd[PATH_MAX];

	getcwd(temp_cwd, PATH_MAX);
	ft_free_and_del(sh->cwd);
	if (!(sh->cwd = ft_strdup(temp_cwd)))
		exit_and_free("malloc error\n");
	return (SUCCESS);
}

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

int			check_sla(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '.')
			return (ERROR);
		i++;
		if (str[i] != '/')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
