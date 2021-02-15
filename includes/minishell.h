/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:54:31 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:25:18 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include "libft.h"

# define SUCCESS 0
# define ERROR 1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/*
**For t_cmdio->outmode
** -WRITE  for ">"
** -APPEND for ">>"
*/
# define WRITE 0
# define APPEND 1

# define BUFF_SIZE 1024

# define DFL_PROMPT	"\33[45m\33[1mminishell\33[49m\33[35m $ \33[0m"


typedef	struct	s_cmdio
{
	char	*in;
	char	*out;
	int		outmode;
}				t_cmdio;

char			*next_cmd(char *prompt, FILE *fp);
void			freelist(char **list);
int				execute(char *argv[]);
void			fatal(char *s1, char *s2, int n);
char			**parse(char *cmdl);
int				strlistlen(char **strlist);
int				redirection_read(char ***argv, int i);
int				redirection_append(char ***argv, int i);
int				redirection_write(char ***argv, int i);

#endif
