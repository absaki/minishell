/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:04:09 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/19 01:30:10 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	char	*cmdline;
	char	*prompt;
	char	**arglist;
	int		result;
	t_sh	*sh;
	
	sh = make_new_sh();
	init_env(sh, envp);
	init_senv(sh, envp);
	prompt = DFL_PROMPT;
	while ((cmdline = next_cmd(prompt, stdin)) != NULL)
	{
		if ((arglist = parse(cmdline)) != NULL)
		{
			result = execute(sh, arglist);
			freelist(arglist);
		}
		free(cmdline);
	}
	return (result);
	(void)argc;
	(void)argv;
}

void	setup(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s,%s\n", s1, s2);
	exit(n);
}
