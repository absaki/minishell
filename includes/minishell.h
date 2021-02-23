/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:54:31 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/23 19:14:48 by kdoi             ###   ########.fr       */
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
	char			*vl;
	struct s_env	*next;
}				t_env;

typedef struct	s_sh
{
	// t_token			*start;
	t_env			*env;
	t_env			*senv;
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
	int				did_cd;
	int				unset_pwd;
	int				unset_oldpwd;
	int				unset_pwd_s;
	int				unset_oldpwd_s;
}				t_sh;

int				ft_pwd(void);
int				ft_echo(char **args);
void			ft_exit(t_sh *sh, char **args);
int				ft_env(char **args, t_env *env, int unset_pwd, int unset_oldpwd);
int				ft_cd(char **args, t_sh *sh);
int				ft_export(char **args, t_env *env, t_env *secret, t_sh *sh);
int				ft_export_loop(char **args, t_env *env, t_env *secret, t_sh *sh);
char			*convert_env_to_str(t_env *lst);
void			sort_env_by_asc(char **tab, int env_len);
int				ft_unset(char **args, t_sh *sh);
void			check_args_in_unset(char *str, t_sh *sh);
void			print_error_in_unset(char *arg);

int				init_env(t_sh *sh, char **env_array);
int				init_senv(t_sh *sh, char **env_array);
int				is_valid_env(const char *str);
int				env_add(const char *value, t_env *env);
char			*get_env_name(char *dest, const char *src);
int				is_in_env(t_env *env, char *args);

void			*malloc_with_list_malloc(size_t size);
void			add_list_malloc(void *ptr);
void			*ft_malloc(void *ptr);
void			free_list_malloc(void);

t_sh			*make_new_sh(void);
char			*ft_strdup_and_list_malloc(const char *s1);
void			free_tda(char **tab);
void			exit_and_free(char *s);

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
int				execute(t_sh *sh, char *argv[]);
void			fatal(char *s1, char *s2, int n);
char			**parse(char *cmdl);
int				strlistlen(char **strlist);
int				redirection_read(char ***argv, int i);
int				redirection_append(char ***argv, int i);
int				redirection_write(char ***argv, int i);

#endif
