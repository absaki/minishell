/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:44:26 by kike              #+#    #+#             */
/*   Updated: 2021/03/14 23:06:33 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_rd(t_sh *sh, char *rdfile, int mode, int pos)
{
	t_rdlist *new;
	t_rdlist *add;

	add = sh->rdlist;
	if (ft_strlen(rdfile) == 0)
		return (-1);
	if ((new = malloc(sizeof(t_rdlist))) == NULL)
		no_mem();
	new->next = NULL;
	new->content = t_rd_dup(rdfile, mode);
	while (add && add->next)
		add = add->next;
	if (!add)
		sh->rdlist = new;
	else
		add->next = new;
	return (pos);
}

static int		store_filename(t_sh *sh, char **s, int pos, int mode)
{
	char *tmp;

	if ((tmp = malloc(sizeof(char))) == NULL)
		no_mem();
	tmp[0] = 0;
	while ((*s)[pos] && (*s)[pos] == ' ')
		pos++;
	while ((*s)[pos])
	{
		if ((*s)[pos] == ' ' || (*s)[pos] == '<' || (*s)[pos] == '>')
			break ;
		else if ((*s)[pos] == '\'')
			pos += s_quote(&(*s)[pos], &tmp);
		else if ((*s)[pos] == '\"')
			pos += d_quote(&(*s)[pos], sh, &tmp);
		else if ((*s)[pos] == '$')
			pos += dollar(&(*s)[pos], sh, &tmp, 1);
		else if ((*s)[pos] == '\\' && (*s)[pos + 1])
			pos += (joinlast_onechr((*s)[pos + 1], &tmp) + 1);
		else
			pos += joinlast_onechr((*s)[pos], &tmp);
	}
	return (set_rd(sh, tmp, mode, pos));
}

int				redirection_parse(t_sh *sh, char **s)
{
	int i;
	int pos;
	int rd;
	int par;

	i = 0;
	par = 0;
	pos = 0;
	while (*s && sh)
	{
		if (pos == -1 || (*s)[i] == '\0')
			break ;
		par = flag_p((*s)[i], par, i > 0 ? (*s)[i - 1] : 0);
		if (!par && ((rd = is_num_rd(&(*s), i))
		|| (rd = is_nonum_rd(&(*s), i))))
		{
			pos = store_filename(sh, &(*s), i, rd);
			if (pos != -1)
				substrend(&(*s), i, pos - 1);
		}
		else
			i++;
	}
	return ((par || pos < 0) ? ERROR : SUCCESS);
}
