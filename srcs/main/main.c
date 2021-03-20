/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:04:09 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/20 23:48:27 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sigstatus g_sig;

static t_sh		*setup(char **envp)
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

static int		islong(char *cmdline)
{
	if (ft_strlen(cmdline) > 1024)
	{
		ft_putendl_fd("too long", 2);
		return (1);
	}
	return (0);
}

static void		while_init(char *cmdline)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	if (cmdline)
	{
		free(cmdline);
		cmdline = 0;
	}
}

int				main(int argc, char **argv, char **envp)
{
	char *cmdline;
	t_sh *sh;

	sh = setup(envp);
	cmdline = 0;
	while (argc || argv)
	{
		while_init(cmdline);
		ft_putstr_fd(sh->prompt, STDERR);
		if ((cmdline = next_cmd()) == NULL)
			break ;
		if (islong(cmdline))
			continue ;
		if (g_sig.sigint && !(g_sig.sigint = 0))
			continue ;
		sh->cmdlist = sep_list(cmdline);
		if (sh->cmdlist == NULL && ft_strlen(cmdline) != 0)
			ft_putendl_fd("sytax error", STDERR);
		if (sh->cmdlist)
			pipemap(sh);
		ft_lstclear(&(sh->cmdlist), (void (*)(void *))free_cmd);
	}
	return (g_sig.status);
}
