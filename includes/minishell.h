/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 19:09:05 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/04 23:24:43 by kdoi             ###   ########.fr       */
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

int				init_env(t_sh *sh, char **env_array);
int				init_secret_env(t_sh *sh, char **env_array);
void			*malloc_with_list_malloc(size_t size);
void			add_list_malloc(void *ptr);
void			*ft_malloc(void *ptr);
void			free_list_malloc(void);
#endif
