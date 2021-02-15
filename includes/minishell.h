/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2020/12/12 19:09:05 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/15 13:20:39 by kikeda           ###   ########.fr       */
=======
/*   Created: 2021/02/02 21:54:31 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/15 13:25:18 by kikeda           ###   ########.fr       */
>>>>>>> kikeda-dev
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
# define BUFF_SIZE 1024

extern t_list	*g_list_malloc;

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_sh
{
	// t_token			*start;
	t_env			*env;
	t_env			*secret_env;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				no_exec;
}				t_sh;

int				ft_pwd(void);
int				ft_echo(char **args);
void			ft_exit(t_sh *sh, char **args);
int				ft_env(t_env *env);
int				ft_cd(char **args, t_env *env);

int				init_env(t_sh *sh, char **env_array);
int				init_secret_env(t_sh *sh, char **env_array);
int				env_add(const char *value, t_env *env);
char			*get_env_name(char *dest, const char *src);
int				is_in_env(t_env *env, char *args);

void			*malloc_with_list_malloc(size_t size);
void			add_list_malloc(void *ptr);
void			*ft_malloc(void *ptr);
void			free_list_malloc(void);

/*
**For t_cmdio->outmode
** -WRITE  for ">"
** -APPEND for ">>"
*/
# define WRITE 0
# define APPEND 1

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
