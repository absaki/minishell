/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:44:26 by kike              #+#    #+#             */
/*   Updated: 2021/03/11 14:38:01 by kikeda           ###   ########.fr       */
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

int is_nonum_rd(char *str, int *i)
{
    if (!ft_strncmp(">>", str, 2) && ((*i) = (*i) + 1))
        return (4);
    if (!ft_strncmp(">", str, 1))
        return (2);
    if (!ft_strncmp("<", str, 1))
        return (1);
    return (0);
}

int is_num_rd(char *str, int *i)
{
    if (!ft_strncmp("1>>", str, 3) && ((*i) = (*i) + 2))
        return (4);
    if (!ft_strncmp("2>>", str, 3) && ((*i) = (*i) + 2))
        return (5);
    if (!ft_strncmp("1>", str, 2) && ((*i) = (*i) + 1))
        return (2);
    if (!ft_strncmp("2>", str, 2) && ((*i) = (*i) + 1))
        return (3);
    if (!ft_strncmp("0<", str, 2) && ((*i) = (*i) + 1))
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
    printf("fd=%d,append=%d,str=\"%s\"\n", new->fd, new->f_append, new->file);
    return (new);
}

void    set_rd(t_sh *sh, char *rdfile, int mode)
{
    t_rdlist *new;

    if((new = malloc(sizeof(t_rdlist))) == NULL)
        no_mem();
    new->next = NULL;
    new->content = t_rd_dup(rdfile, mode);
    while(sh->rdlist)
        sh->rdlist = sh->rdlist->next;
    sh->rdlist = new;
}

int    store_filename(t_sh *sh, char **rtn, int pos, int mode)
{
    char *tmp;

	tmp = malloc(sizeof(char));
	tmp[0] = 0;
	while ((*rtn)[pos] && (*rtn)[pos] == ' ')
		pos++;
	while ((*rtn)[pos])
	{
		if ((*rtn)[pos] == ' ' || (*rtn)[pos] == '<' || (*rtn)[pos] == '>')
			break ;
		else if ((*rtn)[pos] == '\'')
			pos += s_quote(&(*rtn)[pos], &tmp);
		else if ((*rtn)[pos] == '\"')
			pos += d_quote(&(*rtn)[pos], sh, &tmp);
		else if ((*rtn)[pos] == '$')
			pos += dollar(&(*rtn)[pos], sh, &tmp, 1);
		else if ((*rtn)[pos] == '\\' && (*rtn)[pos + 1])
			pos += (joinlast_onechr((*rtn)[pos + 1], &tmp) + 1);
		else
			pos += joinlast_onechr((*rtn)[pos], &tmp);
	}
    if (ft_strlen(tmp) == 0)
        return (-1);
    set_rd(sh, tmp, mode);
    return (pos - 1);
}

char  *redirection_parse(t_sh *sh, char *s)
{
    int i;
    int rd;
    int par;
    char *rtn;

    i = 0;
    par = 0;
    if((rtn = ft_strdup(s)) == NULL)
        no_mem();
    while (s && sh)
    {
        par = flag_p(s[i], par, i > 0 ? s[i - 1] : 0);
        if (!par && ((rd = is_num_rd(&(s[i]), &i)) || (rd = is_nonum_rd(&(s[i]), &i))))
            i = store_filename(sh, &rtn, i + 1, rd);
        if (i == -1 || s[i] == '\0')
            break ;
        i++;
    }
    rtn = s;
    return ((par || i < 0) ? 0 : rtn);
}
