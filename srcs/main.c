/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:04:09 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/06 22:25:43 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(void)
{
	char	*cmdline;
	char	*prompt;
	char	**arglist;
	int		result;

	prompt = DFL_PROMPT;
	while ((cmdline = next_cmd(prompt, stdin)) != NULL)
	{
		if ((arglist = parse(cmdline)) != NULL)
		{
			result = execute(arglist);
			freelist(arglist);
		}
		free(cmdline);
	}
	return (result);
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
