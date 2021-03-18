/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsearch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:49:27 by kike              #+#    #+#             */
/*   Updated: 2021/03/18 16:58:36 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**trim_pathlist(char **rawlist)
{
	int		i;
	int		len;
	char	**rtn;
	char	*tmp;

	i = 0;
	while (rawlist[i])
		i++;
	len = i;
	rtn = my_malloc(sizeof(char *) * (len + 1));
	rtn[len] = NULL;
	i = 0;
	while (rawlist[i])
	{
		if (ft_strlen(rawlist[i]) == 0)
		{
			tmp = safe_strdup(".");
			rtn[i] = tmp;
		}
		else
			rtn[i] = safe_strdup(rawlist[i]);
		i++;
	}
	freelist(rawlist);
	return (rtn);
}

static char		*do_serch(char **pathlist, char *file)
{
	int			i;
	struct stat	statvar;
	char		*tmp;
	char		*full;

	i = 0;
	if ((tmp = ft_strjoin("/", file)) == NULL)
		no_mem();
	while (pathlist[i])
	{
		full = ft_strjoin(pathlist[i], tmp);
		if (stat(full, &statvar) == 0)
		{
			if (S_IXUSR & statvar.st_mode
	|| S_IXGRP & statvar.st_mode || S_IXOTH & statvar.st_mode)
			{
				free(tmp);
				return (full);
			}
		}
		free(full);
		i++;
	}
	free(tmp);
	return (NULL);
}

static char		*serch_path(char *file, t_env *env)
{
	char		**pathlist;
	char		*full;
	char		*pathstr;

	pathstr = get_env_value("PATH", env);
	if ((pathlist = ft_split_empty(pathstr, ':')) == NULL)
		no_mem();
	free(pathstr);
	pathlist = trim_pathlist(pathlist);
	full = do_serch(pathlist, file);
	freelist(pathlist);
	if (full == NULL)
	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd("command not found", STDERR);
	}
	return (full);
}

static int		is_directory(char *fullpath)
{
	struct stat stat_st;

	if (stat(fullpath, &stat_st) == 0 && S_ISDIR(stat_st.st_mode))
		return (1);
	return (0);
}

int				my_execvp(char *file, char **argv, t_sh *sh)
{
	char *cmdpath;
	char **envp;

	if (ft_strchr(file, '/') == 0)
		cmdpath = serch_path(file, sh->env);
	else
		cmdpath = file;
	if (is_directory(cmdpath))
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
