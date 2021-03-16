/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:04:09 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/16 14:20:11 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sigstatus g_sig;

static t_sh	*setup(char **envp)
{
	t_sh *sh;

	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	sh = make_new_sh();
	sh->prompt = DFL_PROMPT;
	init_env(sh, envp);
	init_senv(sh, envp);
	set_shlvl(sh);
	return (sh);
}

int			islong(char *cmdline)
{
	if (ft_strlen(cmdline) > 1024)
	{
		ft_putendl_fd("too long", 2);
		free(cmdline);
		cmdline = 0;
		return (1);
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	char *cmdline;
	t_sh *sh;

	sh = setup(envp);
	while ((cmdline = next_cmd(sh->prompt)) != NULL)
	{
		if (islong(cmdline))
			continue ;
		sh->cmdlist = sep_list(cmdline);
		if (sh->cmdlist == NULL)
			ft_putendl_fd("sytax error", STDERR);
		if (sh->cmdlist)
			pipemap(sh);
	}
	return (g_sig.status);
	(void)argc;
	(void)argv;
}
