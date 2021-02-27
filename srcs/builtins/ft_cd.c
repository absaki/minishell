/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:33:09 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/27 23:49:47 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_env_path(t_env *env, const char *var, size_t len)
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

static int		update_pwd(t_sh *sh)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	if (!(pwd = ft_strjoin("PWD=", cwd)))
		return (ERROR);
	if (is_in_env(sh->env, pwd) == 0)
		env_add(pwd, sh->env);
	if (is_in_env(sh->senv, pwd) == 0)
		env_add(pwd, sh->senv);
	ft_free_and_del(pwd);
	if (sh->unset_pwd == 1 && sh->unset_pwd_s == 0)
		sh->unset_pwd = 0;
	return (SUCCESS);
}

static	int		update_oldpwd(t_sh *sh, char *pre_cwd)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	if (!(oldpwd = ft_strjoin("OLDPWD=", pre_cwd)))
		return (ERROR);
	if (is_in_env(sh->env, oldpwd) == 0)
		env_add(oldpwd, sh->env);
	if (is_in_env(sh->senv, oldpwd) == 0)
		env_add(oldpwd, sh->senv);
	ft_free_and_del(oldpwd);
	if (sh->unset_oldpwd == 1 && sh->unset_oldpwd_s == 0)
		sh->unset_oldpwd = 0;
	return (SUCCESS);
}

static	int		go_to_path(int option, t_sh *sh)
{
	int		cd_ret;
	char	*env_path;
	char	pre_cwd[PATH_MAX];

	if (getcwd(pre_cwd, PATH_MAX) == NULL)
		return (ERROR);
	env_path = NULL;
	env_path = get_env_path(sh->env, "HOME", 4);
	if (!env_path)
		ft_putendl_fd("bash : cd: HOME not set", STDERR);
	if (!env_path)
		return (ERROR);
	cd_ret = chdir(env_path);
	if (cd_ret < 0)
		cd_ret *= -1;
	if (cd_ret != 0)
		print_error_and_set_errno(env_path);
	if (cd_ret > 0 && option == 1)
		ft_putendl_fd(env_path, 1);
	update_oldpwd(sh, pre_cwd);
	update_pwd(sh);
	ft_free_and_del(env_path);
	return (cd_ret);
}

int				ft_cd(char **args, t_sh *sh)
{
	int		cd_ret;
	char	pre_cwd[PATH_MAX];

	if (!args[1])
		cd_ret = go_to_path(0, sh);
	else
	{
		if (getcwd(pre_cwd, PATH_MAX) == NULL)
			return (ERROR);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error_and_set_errno(args[1]);
		if (cd_ret == 0)
		{
			update_oldpwd(sh, pre_cwd);
			update_pwd(sh);
		}
	}
	if (cd_ret == SUCCESS)
		sh->did_cd = 1;
	return (cd_ret);
}
