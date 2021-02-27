/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 18:23:04 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/22 16:36:40 by kikeda           ###   ########.fr       */
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
	waitpid(sh->pid, &child_info, WUNTRACED);
	sh->pipin = -1;
	sh->pipout = -1;
}

int	pipemap(t_sh *sh)
{
	t_cmd		*cmd;

	while(sh->cmdlist && (cmd = sh->cmdlist->content))
	{
		exec_pipe(sh);
		sh->cmdlist = sh->cmdlist->next;
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
