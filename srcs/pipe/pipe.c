/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 18:23:04 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/21 14:47:07 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		do_wait(t_sh *sh)
{
	g_sig.pid = sh->pid;
	waitpid(g_sig.pid, &g_sig.status, WUNTRACED);
	while (wait(NULL) > 0)
		(void)SUCCESS;
	if (WIFEXITED(g_sig.status))
		g_sig.status = WEXITSTATUS(g_sig.status);
	else if (WIFSIGNALED(g_sig.status))
		g_sig.status = WTERMSIG(g_sig.status);
	g_sig.pid = 0;
	sh->pipin = -1;
	sh->pipout = -1;
}

static int		exec_pipe_err(t_sh *sh, char **argv)
{
	ft_putendl_fd("syntax error", STDERR);
	g_sig.status = 2;
	freelist(argv);
	ft_lstclear(&(sh->rdlist), (void (*)(void *))rd_free);
	return (ERROR);
}

static int		exec_pipe(t_sh *sh)
{
	t_cmd	*cmd;
	char	**argv;

	while (sh->cmdlist)
	{
		cmd = sh->cmdlist->content;
		if (cmd->conn == CONN_END && is_space_or_empty(cmd->cmds))
			break ;
		if ((cmd->conn == CONN_PIPE && (cmd->cmds)[0] == 0)
		|| ((argv = parse(&(cmd->cmds), sh)) == 0))
			return (exec_pipe_err(sh, argv));
		sh->pid = execute(sh, argv, cmd->conn);
		if (sh->pid == -200)
			return (exec_pipe_err(sh, argv));
		ft_lstclear(&(sh->rdlist), (void (*)(void *))rd_free);
		freelist(argv);
		if (cmd->conn == CONN_SEMIC || cmd->conn == CONN_END)
			break ;
		sh->cmdlist = sh->cmdlist->next;
	}
	do_wait(sh);
	return (SUCCESS);
}

int				pipemap(t_sh *sh)
{
	t_cmd		*cmd;
	t_cmdlist	*front;

	front = sh->cmdlist;
	while (sh->cmdlist && (cmd = sh->cmdlist->content))
	{
		if (exec_pipe(sh) == ERROR)
			break ;
		sh->cmdlist = sh->cmdlist->next;
		if (g_sig.sigint)
			ft_lstclear(&(sh->cmdlist), (void (*)(void *))free_cmd);
	}
	sh->cmdlist = front;
	return (SUCCESS);
}
