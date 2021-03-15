/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:11:39 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/15 11:55:35 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_pipe_semic(char c)
{
	if (c == '|' || c == ';' || c == '\0')
		return (1);
	return (0);
}

static t_cmd	*dup_cmdcontent(char *s, int i, int start)
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

int				flag_p(char c, int status, char beforec)
{
	static int backslashed = 0;

	if (beforec == 0)
		backslashed = 0;
	if (backslashed)
	{
		backslashed = 0;
		return (status);
	}
	if (c == '\\')
	{
		backslashed = 1;
		return (status);
	}
	if (!status && !backslashed && (c == '\"' || c == '\''))
		return ((int)c);
	if (!status && !backslashed && c == '{')
		return ((int)'}');
	else if (status && !backslashed && (c == status))
		return (0);
	backslashed = 0;
	return (status);
}

t_cmdlist		*sep_list(char *s)
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
		parenthesis = flag_p(s[i], parenthesis, i > 0 ? s[i - 1] : 0);
		if (!parenthesis && is_pipe_semic(s[i]))
		{
			newitem = ft_lstnew(dup_cmdcontent(s, i, start));
			ft_lstadd_back(&rtn, newitem);
			start = i + 1;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (parenthesis ? NULL : rtn);
}

char			**parse(char **cmdl, t_sh *sh)
{
	char		**arglist;

	if (redirection_parse(sh, cmdl) == SUCCESS)
	{
		arglist = split_args(*cmdl, sh);
		return (arglist);
	}
	else
		return (0);
}
