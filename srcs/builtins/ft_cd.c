/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 22:33:09 by kdoi              #+#    #+#             */
/*   Updated: 2021/03/13 19:10:49 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		update_pwd(t_sh *sh)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		exit_and_free("malloc error\n");
	if (!(pwd = ft_strjoin("PWD=", cwd)))
		exit_and_free("malloc error\n");
	if (is_in_env(sh->env, pwd) == 0)
		env_add(pwd, sh->env);
	if (is_in_env(sh->senv, pwd) == 0)
		env_add(pwd, sh->senv);
	ft_free_and_del(pwd);
	if (sh->unset_pwd == 1 && sh->unset_pwd_s == 0)
		sh->unset_pwd = 0;
	return (SUCCESS);
}

static	int		update_oldpwd(t_sh *sh)
{
	char	*oldpwd;
	char	*temp;

	if (check_env_value("PWD", sh->env) != NULL)
	{
		if (!(temp = get_env_value("PWD", sh->env)))
			exit_and_free("malloc error\n");
		if (!(oldpwd = ft_strjoin("OLDPWD=", temp)))
			exit_and_free("malloc error\n");
		if (is_in_env(sh->env, oldpwd) == 0)
			env_add(oldpwd, sh->env);
		if (is_in_env(sh->senv, oldpwd) == 0)
			env_add(oldpwd, sh->senv);
		ft_free_and_del(oldpwd);
		if (sh->unset_oldpwd == 1 && sh->unset_oldpwd_s == 0)
			sh->unset_oldpwd = 0;
	}
	else
	{
		if (is_in_env(sh->env, "OLDPWD=") == 0)
			env_add(oldpwd, sh->env);
		if (is_in_env(sh->senv, "OLDPWD=") == 0)
			env_add(oldpwd, sh->senv);
	}
	return (SUCCESS);
}

static	int		go_home(t_sh *sh)
{
	int		cd_ret;
	char	*env_path;

	env_path = get_env_path(sh->env, "HOME", 4);
	if (!env_path)
		ft_putendl_fd("bash : cd: HOME not set", STDERR);
	if (!env_path)
		return (ERROR);
	cd_ret = chdir(env_path);
	if (cd_ret != 0)
	{
		print_error_and_set_errno(env_path);
		return (ERROR);
	}
	update_oldpwd(sh);
	update_pwd(sh);
	update_cwd(sh);
	ft_free_and_del(env_path);
	return (cd_ret);
}

static	int		cd_in_rf(t_sh *sh)
{
	char	*temp;
	char	*pwd;

	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories:", 2);
	ft_putendl_fd(" No such file or directory", 2);
	update_oldpwd(sh);
	if (!(temp = ft_strdup(sh->cwd)))
		exit_and_free("malloc error\n");
	ft_free_and_del(sh->cwd);
	if (!(sh->cwd = ft_strjoin(temp, "/.")))
		exit_and_free("malloc error\n");
	if (!(pwd = ft_strjoin("PWD=", sh->cwd)))
		exit_and_free("malloc error\n");
	if (is_in_env(sh->env, pwd) == 0)
		env_add(pwd, sh->env);
	if (is_in_env(sh->senv, pwd) == 0)
		env_add(pwd, sh->senv);
	return (SUCCESS);
}

int				ft_cd(char **args, t_sh *sh)
{
	char	cwd[PATH_MAX];
	int		cd_ret;

	if (!args[1])
		cd_ret = go_home(sh);
	else if (ft_strcmp(args[1], ".") == 0 && getcwd(cwd, PATH_MAX) == NULL)
		cd_ret = cd_in_rf(sh);
	else
	{
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error_and_set_errno(args[1]);
		if (cd_ret == 0)
		{
			update_oldpwd(sh);
			update_pwd(sh);
			update_cwd(sh);
		}
	}
	if (cd_ret == SUCCESS)
		sh->did_cd = 1;
	return (cd_ret);
}
