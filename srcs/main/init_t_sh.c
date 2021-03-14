/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:36:05 by kdoi              #+#    #+#             */
/*   Updated: 2021/03/14 18:51:16 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*set_cwd(void)
{
	char	temp_cwd[PATH_MAX];
	char	*cwd;

	if (getcwd(temp_cwd, PATH_MAX) == NULL)
		exit_and_free("this directory is removed\n");
	if (!(cwd = ft_strdup(temp_cwd)))
		exit_and_free("malloc error\n");
	return (cwd);
}

t_sh			*make_new_sh(void)
{
	t_sh	*sh;

	sh = (t_sh *)my_malloc(sizeof(t_sh));
	sh->cwd = set_cwd();
	sh->in = 0;
	sh->out = 0;
	sh->fdin = 0;
	sh->fdout = 0;
	sh->pipin = -1;
	sh->pipout = -1;
	sh->pid = 0;
	sh->charge = 0;
	sh->parent = 0;
	sh->last = 0;
	sh->ret = 0;
	sh->exit = 0;
	sh->no_exec = 0;
	sh->did_cd = 0;
	sh->unset_pwd = 0;
	sh->unset_oldpwd = 0;
	sh->unset_pwd_s = 0;
	sh->unset_oldpwd_s = 0;
	sh->rdlist = 0;
	add_list_malloc(sh);
	return (sh);
}
