/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:44:26 by kike              #+#    #+#             */
/*   Updated: 2021/03/12 17:27:02 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
// REDIRECTION INT
// 0:   NOP
// 1:   STDIN
// 2:   STDOUT WRITE
// 3:   STDERR WRITE
// 4:   STDOUT APPEND
// 5:   STDERR APPEND
*/

int is_nonum_rd(char **str, int i)
{
    if (!ft_strncmp(">>", &(*str)[i], 2) && !substrend(str, i, i + 1))
        return (4);
    if (!ft_strncmp(">", &(*str)[i], 1) && !substrend(str, i, i))
        return (2);
    if (!ft_strncmp("<", &(*str)[i], 1) && !substrend(str, i, i))
        return (1);
    return (0);
}

int is_num_rd(char **str, int i)
{
    if (!ft_strncmp("1>>", &(*str)[i], 3) && !substrend(str, i, i + 2))
        return (4);
    if (!ft_strncmp("2>>", &(*str)[i], 3) && !substrend(str, i, i + 2))
        return (5);
    if (!ft_strncmp("1>", &(*str)[i], 2) && !substrend(str, i, i + 1))
        return (2);
    if (!ft_strncmp("2>", &(*str)[i], 2) && !substrend(str, i, i + 1))
        return (3);
    if (!ft_strncmp("0<", &(*str)[i], 2) && !substrend(str, i, i + 1))
        return (1);
    return (0);
}

t_redirection *t_rd_dup(char *rdfile, int mode)
{
    t_redirection *new;

    if((new = malloc(sizeof(t_redirection))) == NULL)
        no_mem();
    if(mode == 1)
        new->fd = 0;
    else if(mode == 2 || mode == 4)
        new->fd = 1;
    else if(mode == 3 || mode == 5)
        new->fd = 2;
    if(mode == 1 || mode == 2 || mode == 3)
        new->f_append = 0;
    else if(mode == 4 || mode == 5)
        new->f_append = 1;
    if(rdfile)
        new->file = rdfile;
    return (new);
}

int    set_rd(t_sh *sh, char *rdfile, int mode, int pos)
{
    t_rdlist *new;

    if (ft_strlen(rdfile) == 0)
        return (-1);
    if((new = malloc(sizeof(t_rdlist))) == NULL)
        no_mem();
    new->next = NULL;
    new->content = t_rd_dup(rdfile, mode);
    while(sh->rdlist)
        sh->rdlist = sh->rdlist->next;
    sh->rdlist = new;
    return (pos);
}

int    store_filename(t_sh *sh, char **s, int pos, int mode)
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

int     redirection_parse(t_sh *sh, char **s)
{
    int i;
    int pos;
    int rd;
    int par;

    i = 0;
    par = 0;
    while (*s && sh)
    {
        par = flag_p((*s)[i], par, i > 0 ? (*s)[i - 1] : 0);
        if (!par && ((rd = is_num_rd(&(*s), i)) || (rd = is_nonum_rd(&(*s), i))))
        {
            pos = store_filename(sh, &(*s), i, rd);
            if(pos != -1)
                substrend(&(*s), i, pos - 1);
        }
        else if (i == -1 || (*s)[i] == '\0')
            break ;
        else
            i++;
    }
    return ((par || i < 0) ? ERROR : SUCCESS);
}
