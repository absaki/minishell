/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:12:38 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/24 14:01:33 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_fd(t_sh *sh, char ***argv)
{
	int i;

	(void)sh;
	i = 0;
	while ((*argv)[i])
	{
		i -= redirection_write(argv, i);
		i -= redirection_error(argv, i);
		i -= redirection_append(argv, i);
		i -= redirection_append_err(argv, i);
		i -= redirection_read(argv, i);
		i++;
	}
}

int buk_fds(int fds[3])
{
	fds[0] = dup(0);
	fds[1] = dup(1);
	fds[2] = dup(2);
	
	if(fds[0] && fds[1] && fds[2])
		return (SUCCESS);
	else
		return (ERROR);
}

int reset_fds(int fds[3])
{
	if(
		dup2(fds[0], 0) != -1
		&& dup2(fds[1], 1) != -1
		&& dup2(fds[2], 2) != -1
		&& close(fds[0]) != -1
		&& close(fds[1]) != -1
		&& close(fds[2]) != -1)
	{
		return (SUCCESS);		
	}
	return (ERROR);
}

int do_builtin(t_sh *sh, char **argv)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		ft_echo(argv);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		ft_env(argv, sh->env, sh->unset_pwd, sh->unset_oldpwd);
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		ft_exit(sh, argv);
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		ft_export(argv, sh->env, sh->senv, sh);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		ft_unset(argv, sh);
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
		ft_cd(argv, sh);
	else
		return (0);
	return (1);
}

int is_builtin_nopipe(t_sh *sh, char **argv, int newpipe[2])
{
	int fds[3];

	if (newpipe[0] != -1 && newpipe[1] != -1)
		return (0);
	if (!ft_strncmp(argv[0], "echo", 5)
		|| !ft_strncmp(argv[0], "env", 4)
		|| !ft_strncmp(argv[0], "exit", 5)
		|| !ft_strncmp(argv[0], "export", 7)
		|| !ft_strncmp(argv[0], "pwd", 4)
		|| !ft_strncmp(argv[0], "unset", 6)
		|| !ft_strncmp(argv[0], "cd", 3))
	{
		buk_fds(fds);
		set_fd(sh, &argv);
		do_builtin(sh, argv);
		reset_fds(fds);
		return (1);
	}
	return (0);
}

void exec_child(t_sh *sh, char **argv, int newpipe[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (sh->pipin != -1) //haspipe
	{
		close(sh->pipin);
		dup2(sh->pipout, 0);
		close(sh->pipout);
	}
	if (newpipe[0] != -1) //ispipe
	{
		close(newpipe[0]);
		dup2(newpipe[1], 1);
		close(newpipe[1]);
	}
	set_fd(sh, &argv);
	if(do_builtin(sh, argv))
		exit (EXIT_SUCCESS);
	execvp(argv[0], argv);
	perror("cannot execute command");
	exit(1);
}

int execute(t_sh *sh, char *argv[], int conn)
{
	int pid;
	int newpipe[2];

	newpipe[0] = -1;
	if (argv[0] == NULL)
		return (SUCCESS);
	if (conn == CONN_PIPE)
		pipe(newpipe);
	if (is_builtin_nopipe(sh, argv, newpipe))
		return (SUCCESS);
	if ((pid = fork()) == -1)
		perror("fork");
	else if (pid == 0)
		exec_child(sh, argv, newpipe);
	else
	{
		if (sh->pipin != -1) //haspipe
		{
			close(sh->pipin);
			close(sh->pipout);
		}
		if (newpipe[0] != -1) //ispipe
		{
			sh->pipout = newpipe[0];
			sh->pipin = newpipe[1];
		}
	}
	return (pid);
}
