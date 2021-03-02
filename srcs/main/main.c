/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kike <kike@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:04:09 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/02 14:35:15 by kike             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sigstatus g_sig;

void	setup(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}

int		main(int argc, char **argv, char **envp)
{
	char	*cmdline;
	char	*prompt;
	// char	**arglist;
	int		result = SUCCESS;
	t_sh	*sh;

	setup();
	sh = make_new_sh();
	init_env(sh, envp);
	init_senv(sh, envp);
	prompt = DFL_PROMPT;
	while ((cmdline = next_cmd(prompt, stdin)) != NULL)
	{
		sh->cmdlist = sep_list(cmdline);
		if(sh->cmdlist)
			pipemap(sh);
		// if ((arglist = parse(cmdline)) != NULL)
		// {
		// 	result = execute(sh, arglist);
		// 	freelist(arglist);
		// }
		// free(cmdline);
	}
	return (result);
	(void)argc;
	(void)argv;
}

void	fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s,%s\n", s1, s2);
	exit(n);
}
