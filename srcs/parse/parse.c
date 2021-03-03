/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kike <kike@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:11:39 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/04 00:26:45 by kike             ###   ########.fr       */
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
		no_mem();
	if ((rtn->cmds = ft_substr(s, start, i - start)) == NULL)
		no_mem();
	if (s[i] == '|')
		rtn->conn = CONN_PIPE;
	else if (s[i] == ';')
		rtn->conn = CONN_SEMIC;
	else if (s[i] == '\0')
		rtn->conn = CONN_END;
	return (rtn);
}

int			flag_parenthesis(char c, int status, char beforec)
{
	if (beforec == '\\')
		return (status);
	if (!status && (c == '\"' || c == '\''))
		return ((int)c);
	if (!status && c == '{')
		return ((int)'}');
	else if (status && (c == status))
		return (0);
	return (status);
}

t_cmdlist	*sep_list(char *s)
{
	int			i;
	int			start;
	int			parenthesis;
	t_cmdlist	*rtn;
	t_cmdlist	*newitem;

	i = 0;
	start = 0;
	rtn = 0;
	parenthesis = 0;
	while (*s)
	{
		parenthesis = flag_parenthesis(s[i], parenthesis, s[i - 1]);
		if (!parenthesis && is_conjuction(s[i]))
		{
			newitem = ft_lstnew(dup_cmdcontent(s, i, start));
			ft_lstadd_back(&rtn, newitem);
			start = i + 1;
		}
		if(s[i] == '\0')
			break ;
		i++;
	}
	return (rtn);
}

char		**parse(char *cmdl, t_sh *sh)
{
	char		**arglist;
	add_space_front(&cmdl);
	add_space_back(&cmdl);
	arglist = split_args(cmdl, sh);
	// int i = 0;m
	// while(arglist[i])
	// {
	// 	printf("arg[%d]=->%s<-\n", i, arglist[i]);
	// 	i++;
	// }
	// arglist = ft_split(cmdl, ' ');
	return (arglist);
}
