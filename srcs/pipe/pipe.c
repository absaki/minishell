/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 18:23:04 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/06 11:02:00 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_sh *sh)
{
	t_cmd *cmd;
	char	**argv;

	while(sh->cmdlist)
	{
		cmd = sh->cmdlist->content;
		argv = parse(cmd->cmds, sh);
		sh->pid = execute(sh, argv, cmd->conn);
		if(cmd->conn == CONN_SEMIC || cmd->conn == CONN_END)
			break ;
		sh->cmdlist = sh->cmdlist->next;
	}
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

int	pipemap(t_sh *sh)
{
	t_cmd		*cmd;
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	while(sh->cmdlist && (cmd = sh->cmdlist->content))
	{
		if (ft_strlen(cmd->cmds) == 0)
		{
			ft_putendl_fd("syntax error", STDERR);
			g_sig.status = 2;
			break ;
		}
		exec_pipe(sh);
		sh->cmdlist = sh->cmdlist->next;
		if(g_sig.sigint)
			ft_lstclear(&(sh->cmdlist), (void (*)(void *))free_cmd);
	}
	return (SUCCESS);
}
