/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:12:38 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/16 16:44:30 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		do_builtin(t_sh *sh, char **argv)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		g_sig.status = ft_echo(argv);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		g_sig.status = ft_env(argv, sh->env, sh->unset_pwd, sh->unset_oldpwd);
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		ft_exit(sh, argv);
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		g_sig.status = ft_export(argv, sh->env, sh->senv, sh);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		g_sig.status = ft_pwd(sh);
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		g_sig.status = ft_unset(argv, sh);
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
		g_sig.status = ft_cd(argv, sh);
	else
		return (0);
	return (1);
}

static int		is_builtin_nopipe(t_sh *sh, char **argv, int newpipe[2])
{
	int fds[3];

	if (newpipe[0] != -1 || sh->pipin != -1)
		return (0);
	if (!ft_strncmp(argv[0], "echo", 5)
	|| !ft_strncmp(argv[0], "env", 4) || !ft_strncmp(argv[0], "exit", 5)
	|| !ft_strncmp(argv[0], "export", 7) || !ft_strncmp(argv[0], "pwd", 4)
	|| !ft_strncmp(argv[0], "unset", 6) || !ft_strncmp(argv[0], "cd", 3))
	{
		buk_fds(fds);
		if (set_fd(sh) == ERROR)
		{
			g_sig.status = 1;
			return (1);
		}
		do_builtin(sh, argv);
		reset_fds(fds);
		return (1);
	}
	return (0);
}

static void		exec_child(t_sh *sh, char **argv, int newpipe[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (sh->pipin != -1)
	{
		close(sh->pipin);
		dup2(sh->pipout, 0);
		close(sh->pipout);
	}
	if (newpipe[0] != -1)
	{
		close(newpipe[0]);
		dup2(newpipe[1], 1);
		close(newpipe[1]);
	}
	if (set_fd(sh) == ERROR)
		exit(1);
	if (do_builtin(sh, argv))
		exit(g_sig.status);
	my_execvp(argv[0], argv, sh);
	ft_putstr_fd(argv[0], STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
	exit(errno == ENOTDIR ? 126 : 127);
}

static void		print_err(void)
{
	ft_putstr_fd("fork: ", STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
}

int				execute(t_sh *sh, char *argv[], int conn)
{
	int pid;
	int newpipe[2];

	newpipe[0] = -1;
	if (argv[0] == NULL)
		return (-200);
	if (conn == CONN_PIPE)
		pipe(newpipe);
	if (is_builtin_nopipe(sh, argv, newpipe))
		return (0);
	if ((pid = fork()) == -1)
		print_err();
	else if (pid == 0)
		exec_child(sh, argv, newpipe);
	else
	{
		if (sh->pipin != -1 && !close(sh->pipin) && !close(sh->pipout))
			(void)SUCCESS;
		if (newpipe[0] != -1)
		{
			sh->pipout = newpipe[0];
			sh->pipin = newpipe[1];
		}
	}
	return (pid);
}
