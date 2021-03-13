/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:04:09 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/13 14:34:41 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sigstatus g_sig;

t_sh	*setup(char **envp)
{
	t_sh	*sh;

	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	sh = make_new_sh();
	sh->prompt = DFL_PROMPT;
	init_env(sh, envp);
	init_senv(sh, envp);
	set_shlvl(sh);
	return (sh);
}

int		main(int argc, char **argv, char **envp)
{
	char	*cmdline;
	t_sh	*sh;

	sh = setup(envp);
	while ((cmdline = next_cmd(sh->prompt, stdin)) != NULL)
	{
		sh->cmdlist = sep_list(cmdline);
		if(sh->cmdlist)
			pipemap(sh);
	}
	return (g_sig.status);
	(void)argc;
	(void)argv;
}

void	fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s,%s\n", s1, s2);
	exit(n);
}
