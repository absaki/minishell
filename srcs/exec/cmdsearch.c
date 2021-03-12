/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsearch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:49:27 by kike              #+#    #+#             */
/*   Updated: 2021/03/12 21:32:05 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **makepathlist(char *pathstr)
{
    char **pathlist;
    
    if((pathlist = ft_split(pathstr, ':')) == NULL)
        no_mem();
    return (pathlist);
}

char    *serch_path(char *file, t_env *env)
{
    char **pathlist;
    char *tmp;
    char *full;
    int i;
    struct stat statvar;

    tmp = ft_strjoin("/", file);
    pathlist = makepathlist(get_env_value("PATH", env));
    i = 0;
    while(pathlist[i])
    {
        full = ft_strjoin(pathlist[i], tmp);
        if(stat(full, &statvar) == 0)
        {
            if(S_IXUSR & statvar.st_mode
            || S_IXGRP & statvar.st_mode
            || S_IXOTH & statvar.st_mode)
            {
                free(tmp);
                return (full) ;
            }
        }
        i++;
    }
    ft_putstr_fd(file, STDERR);
	ft_putstr_fd(": ", STDERR);
    ft_putendl_fd("command not found", STDERR);
    free(tmp);
    return (NULL);
}

int     is_directory(char *fullpath)
{
    struct stat stat_st;
    
    stat(fullpath, &stat_st);
    if(S_ISDIR(stat_st.st_mode))
        return (1);
    return (0);
}

int     my_execvp(char *file, char **argv, t_sh *sh)
{
    char *cmdpath;
    char **envp;
    
    if(ft_strchr(file, '/') == 0)
        cmdpath = serch_path(file, sh->env);
    else
        cmdpath = file;
    if(is_directory(cmdpath))
    {
        ft_putstr_fd(file, STDERR);
	    ft_putendl_fd(": Is a directory", STDERR);
        exit(126);
    }
    envp = makeenvlist(sh->env);
    if (cmdpath)
        return (execve(cmdpath, argv, envp));
    exit(127);
}
