/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addspace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kike <kike@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 23:20:07 by kike              #+#    #+#             */
/*   Updated: 2021/03/04 00:25:52 by kike             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_space_back(char **cmdl)
{
    char *old;
    char *new;
    int i;
    int j;
    int alnumflag;//0= リダイレクト記号後の通常文字  1=通常文字 3=エスケープ 4=リダイレクト記号

    if((new = malloc(2 * ft_strlen(*cmdl) + 1)) == NULL)
        no_mem();
    old = *cmdl;
    i = 0;
    j = 0;
    alnumflag = 0;
    while(old[i])
    {
        if(old[i] == '\\')
            alnumflag = 3;
        else if(old[i] != '<' && old[i] != '>' && alnumflag == 4)
        {
            alnumflag = 1;
            new[j++] = ' ';
        }
        else if((old[i] == '<' || old[i] == '>') && alnumflag != 3)
            alnumflag = 4;
        else
            alnumflag = 1;
        new[j++] = old[i++];
    }
    new[j] = '\0';
    free(old);
    *cmdl = new;
}

void add_space_front(char **cmdl)
{
    char *old;
    char *new;
    int i;
    int j;
    int alnumflag;//0= リダイレクト記号の先頭  1=通常文字 2=エスケープされていないdigit 3=エスケープ 4=リダイレクト記号の途中

    if((new = malloc(2 * ft_strlen(*cmdl) + 1)) == NULL)
        no_mem();
    old = *cmdl;
    i = 0;
    j = 0;
    alnumflag = 0;
    while(old[i])
    {
        if(old[i] == '\\')
            alnumflag = 3;
        else if(ft_isdigit(old[i]) && alnumflag != 3)
            alnumflag = 2;
        else if((old[i] == '<' || old[i] == '>') && alnumflag != 3 && alnumflag != 0 && alnumflag != 4)
        {
            if(alnumflag != 2)
                new[j++] = ' ';
            alnumflag = 0;
        }
        else if((old[i] == '<' || old[i] == '>') && (alnumflag == 0 || alnumflag == 4))
            alnumflag = 4;
        else
            alnumflag = 1;
        new[j++] = old[i++];
    }
    new[j] = '\0';
    free(old);
    *cmdl = new;
}
