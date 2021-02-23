/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:12:38 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/20 16:50:30 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd(t_sh *sh, char ***argv)
{
	int i;

	(void)sh;
	i = 0;
	while ((*argv)[i])
	{
		i -= redirection_write(argv, i);
		i -= redirection_append(argv, i);
		i -= redirection_read(argv, i);
		i++;
	}
}

int		is_builtin(t_sh *sh, char **argv)
{
	if(ft_strncmp(argv[0], "echo", 5) == 0)
		ft_echo(argv);
	else if(ft_strncmp(argv[0], "env", 4) == 0)
		ft_env(argv, sh->env, sh->unset_pwd, sh->unset_oldpwd);
	else if(ft_strncmp(argv[0], "exit", 5) == 0)
		ft_exit(sh, argv);
	else if(ft_strncmp(argv[0], "export", 7) == 0)
		ft_export(argv, sh->env, sh->senv, sh);
	else if(ft_strncmp(argv[0], "pwd", 4) == 0)
		ft_pwd();
	else if(ft_strncmp(argv[0], "unset", 6) == 0)
		ft_unset(argv, sh);
	else if(ft_strncmp(argv[0], "cd", 3) == 0)
		ft_cd(argv, sh);
	else
		return (0);
	return (1);
}

void	exec_child(t_sh *sh, char **argv)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_fd(sh, &argv);
	execvp(argv[0], argv);
	perror("cannot execute command");
	exit(1);
}

int				execute(t_sh *sh, char *argv[])
{
	int pid;
	int child_info;

	child_info = -1;
	if (argv[0] == NULL)
		return (SUCCESS);
	if(is_builtin(sh, argv))
		return (SUCCESS);
	if ((pid = fork()) == -1)
		perror("fork");
	else if (pid == 0)
		exec_child(sh, argv);
	else
	{
		if (wait(&child_info) == -1)
			perror("wait");
	}
	return (child_info);
}
