/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 18:23:04 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/12 17:18:57 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void do_wait(t_sh *sh)
{
	g_sig.pid = sh->pid;
	waitpid(g_sig.pid, &g_sig.status, WUNTRACED);
	while (wait(NULL) > 0) ;
	if(WIFEXITED(g_sig.status))
		g_sig.status = WEXITSTATUS(g_sig.status);
	else if(WIFSIGNALED(g_sig.status))
		g_sig.status = WTERMSIG(g_sig.status);
	g_sig.pid = 0;
	sh->pipin = -1;
	sh->pipout = -1;
}

int exec_pipe_err(t_sh *sh)
{
	ft_putendl_fd("syntax error", STDERR);
	g_sig.status = 2;
	ft_lstclear(&(sh->rdlist), (void (*)(void *))rd_free);
	return (ERROR);
}

int	exec_pipe(t_sh *sh)
{
	t_cmd *cmd;
	char	**argv;

	while(sh->cmdlist)
	{
		cmd = sh->cmdlist->content;
		if ((cmd->conn ==CONN_PIPE && (cmd->cmds)[0] == 0) || ((argv = parse(&(cmd->cmds), sh)) == 0))
			return(exec_pipe_err(sh));
		sh->pid = execute(sh, argv, cmd->conn);
		if(cmd->conn == CONN_SEMIC || cmd->conn == CONN_END)
			break ;
		sh->cmdlist = sh->cmdlist->next;
	}
	ft_lstclear(&(sh->rdlist), (void (*)(void *))rd_free);
	do_wait(sh);
	return (SUCCESS);
}

int	pipemap(t_sh *sh)
{
	t_cmd		*cmd;
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	while(sh->cmdlist && (cmd = sh->cmdlist->content))
	{
		if(exec_pipe(sh) == ERROR)
			break ;
		sh->cmdlist = sh->cmdlist->next;
		if(g_sig.sigint)
			ft_lstclear(&(sh->cmdlist), (void (*)(void *))free_cmd);
	}
	ft_lstclear(&(sh->cmdlist), (void (*)(void *))free_cmd);
	return (SUCCESS);
}
