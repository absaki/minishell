/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:11:39 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/19 00:18:42 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_conjuction(char c)
{
	if (c == '|' || c == ';' || c == '\0')
		return (1);
	return (0);
}

t_cmd		*dup_cmdcontent(char *s, int i, int start)
{
	t_cmd *rtn;

	if ((rtn = malloc(sizeof(t_cmd))) == NULL)
		exit(1);
	if ((rtn->cmds = ft_substr(s, start, i - start)) == NULL)
		exit(1);
	printf("in dup_cmdcontent: substr = %s\n", rtn->cmds);
	if (s[i] == '|')
		rtn->conn = CONN_PIPE;
	else if (s[i] == ';')
		rtn->conn = CONN_SEMIC;
	else if (s[i] == '\0')
		rtn->conn = CONN_END;
	return (rtn);
}

t_cmdlist	*sep_cmd(char *s)
{
	int			i;
	int			start;
	t_cmdlist	*rtn;
	t_cmdlist	*newitem;

	i = 0;
	start = 0;
	rtn = 0;
	while (*s)
	{
		if (is_conjuction(s[i]))
		{
			newitem = ft_lstnew(dup_cmdcontent(s, i, start));
			ft_lstadd_back(&rtn, newitem);
			start = i + 1;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (rtn);
}

char		**parse(char *cmdl)
{
	char **arglist;

	arglist = ft_split(cmdl, ' ');
	return (arglist);
}
