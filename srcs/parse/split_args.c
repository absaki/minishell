/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:34:02 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/15 12:27:06 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				s_quote(char *s, char **tmp)
{
	int		i;
	int		end;
	char	*new;
	char	*cpy;

	i = 1;
	while (s[i] && s[i] != '\'')
		i++;
	end = i;
	cpy = my_malloc(sizeof(char) * end);
	i = 0;
	while (s[i + 1] && s[i + 1] != '\'')
	{
		cpy[i] = s[i + 1];
		i++;
	}
	cpy[i] = '\0';
	if ((new = ft_strjoin(*tmp, cpy)) == NULL)
		no_mem();
	free(cpy);
	free(*tmp);
	*tmp = new;
	return (i + 2);
}

int				d_quote(char *s, t_sh *sh, char **tmp)
{
	int i;

	i = 1;
	while (s[i] != '\"')
	{
		if (s[i] && s[i] == '$')
			i += dollar(&(s[i]), sh, tmp, 0);
		else if (s[i] == '\\' && s[i + 1])
			i += (joinlast_onechr(s[i + 1], tmp) + 1);
		else if (s[i])
			i += joinlast_onechr(s[i], tmp);
	}
	return (i + 1);
}

int				join_arglist(char **tmp, char ***args, char *s)
{
	int		i;
	int		len;
	char	**rtn;

	i = 0;
	while ((*args)[i])
		i++;
	len = i;
	rtn = (char **)my_malloc(sizeof(char *) * (len + 2));
	i = -1;
	while ((*args)[++i])
		rtn[i] = safe_strdup((*args)[i]);
	freelist(*args);
	rtn[i++] = safe_strdup(*tmp);
	free(*tmp);
	*tmp = my_malloc(sizeof(char) * 1);
	(*tmp)[0] = 0;
	rtn[i] = NULL;
	*args = rtn;
	i = 0;
	while (s[i] == ' ')
		i++;
	return (i);
}

static int		split_one_arg(char *s, int pos, char **tmp, t_sh *sh)
{
	if (s[pos] == '\'')
		return (s_quote(&s[pos], tmp));
	else if (s[pos] == '\"')
		return (d_quote(&s[pos], sh, tmp));
	else if (s[pos] == '$')
		return (dollar(&s[pos], sh, tmp, 1));
	else if (s[pos] == '\\' && s[pos + 1])
		return ((joinlast_onechr(s[pos + 1], tmp) + 1));
	else
		return (joinlast_onechr(s[pos], tmp));
}

char			**split_args(char *s, t_sh *sh)
{
	char	**rtn;
	char	*tmp;
	int		i;

	i = 0;
	tmp = my_malloc(sizeof(char));
	tmp[0] = 0;
	rtn = my_malloc(sizeof(char *));
	rtn[0] = 0;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == ' ')
			i += join_arglist(&tmp, &rtn, &s[i]);
		else
			i += split_one_arg(s, i, &tmp, sh);
	}
	if (tmp[0])
		join_arglist(&tmp, &rtn, &s[i]);
	return (rtn);
}
