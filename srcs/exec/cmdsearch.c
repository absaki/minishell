/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsearch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:49:27 by kike              #+#    #+#             */
/*   Updated: 2021/03/07 23:29:28 by kikeda           ###   ########.fr       */
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
            if(S_IXUSR & statvar.st_mode)
            {
                free(tmp);
                return (full) ;
            }
        }
        i++;
    }
    free(tmp);
    return (NULL);
}

int     my_execvp(char *file, char **argv, t_sh *sh)
{
    char *cmdpath;
    char **envp;
    
    if(ft_strchr(file, '/') == 0)
        cmdpath = serch_path(file, sh->env);
    else
        cmdpath = file;
    envp = makeenvlist(sh->env);
    return (execve(cmdpath, argv, envp));
}
