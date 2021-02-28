/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 18:23:04 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/28 22:57:42 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_sh *sh)
{
	t_cmd *cmd;
	char	**argv;
	int child_info;

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
	waitpid(g_sig.pid, &child_info, 0);
	g_sig.pid = 0;
	sh->pipin = -1;
	sh->pipout = -1;
}

int	pipemap(t_sh *sh)
{
	t_cmd		*cmd;
	g_sig.sigint = 0;
	while(sh->cmdlist && (cmd = sh->cmdlist->content))
	{
		exec_pipe(sh);
		sh->cmdlist = sh->cmdlist->next;
		if(g_sig.sigint)
			ft_lstclear(&(sh->cmdlist), (void (*)(void *))free_cmd);
	}
	// while(list && (cmd = list->content))
	// {
	// 	arglist = parse(cmd->cmds);	
	// 	result = execute(sh, arglist);
	// 	if(cmd->conn == CONN_SEMIC || cmd->conn == CONN_END)
	// 		{
	// 			list = list->next;
	// 			break ;
	// 		}
	// 	list = list->next;
	// }
	return (SUCCESS);
}
