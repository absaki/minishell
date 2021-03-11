/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kike <kike@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:54:31 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/10 21:57:39 by kike             ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/stat.h>
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

# define CONN_PIPE 1
# define CONN_SEMIC 2
# define CONN_END 3

typedef struct s_sigstatus
{
	int		pid;
	int		sigint;
	int		sigquit;
	int		status;
}				t_sigstatus;

extern t_sigstatus g_sig;

extern t_list	*g_list_malloc;

typedef struct			s_cmd
{
	char				*cmds;
	int					conn;
}						t_cmd;

typedef t_list	t_cmdlist;

typedef struct	s_env
{
	char			*vl;
	struct s_env	*next;
}				t_env;

typedef struct s_redirection
{
	int		fd;
	char	*file;
	int		f_append;
}				t_redirection;

typedef t_list t_rdlist;

typedef struct	s_sh
{
	// t_token			*start;
	t_env			*env;
	t_env			*senv;
	t_cmdlist		*cmdlist;
	t_rdlist		*rdlist;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	pid_t			pid;
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
void			print_error_and_set_errno(char *str);
int				ft_export(char **args, t_env *env, t_env *secret, t_sh *sh);
int				ft_export_loop(char **args, t_env *env, t_env *secret, t_sh *sh);
char			*convert_env_to_str(t_env *lst);
void			sort_env_by_asc(char **tab, int env_len);
int				ft_unset(char **args, t_sh *sh);
void			check_args_in_unset(char *str, t_sh *sh);
void			print_error_in_unset(char *arg);
int				ft_isspace(int c);
int				ft_will_overflow(int sign, unsigned long n, int next_digit);
char			*check_env_value(char *arg, t_env *env);


int				init_env(t_sh *sh, char **env_array);
int				init_senv(t_sh *sh, char **env_array);
int				is_valid_env(const char *str);
int				env_add(const char *value, t_env *env);
char			*get_env_name(char *dest, const char *src);
char			*get_env_value(char *arg, t_env *env);
int				is_in_env(t_env *env, char *args);
char			*env_value(char *env);

void			*malloc_with_list_malloc(size_t size);
void			add_list_malloc(void *ptr);
void			*ft_malloc(void *ptr);
void			free_list_malloc(void);

t_sh			*make_new_sh(void);
char			*ft_strdup_and_list_malloc(const char *s1);
void			free_tda(char **tab);
void			exit_and_free(char *s);

t_cmdlist		*sep_list(char *s);
int				pipemap(t_sh *sh);
void			no_mem(void);
int				joinlast_onechr(char c, char **tmp);
char 			**split_args(char *s, t_sh *sh);

void			sig_int(int status);
void			sig_quit(int status);
void			free_cmd(t_cmd *cmd);
int				my_execvp(char *file, char **argv, t_sh *sh);
char			**makeenvlist(t_env *env);
void			add_space_front(char **cmdl);
void			add_space_back(char **cmdl);
int				flag_p(char c, int status, char beforec);
int				dollar(char *s, t_sh *sh, char **tmp, int trim);
int				s_quote(char *s, char **tmp);
int				d_quote(char *s, t_sh *sh, char **tmp);



/*
**For t_cmdio->outmode
** -WRITE  for ">"
** -APPEND for ">>"
*/
# define WRITE 0
# define APPEND 1

# define DFL_PROMPT	"MiniShell$"


typedef	struct	s_cmdio
{
	char	*in;
	char	*out;
	int		outmode;
}				t_cmdio;

char			*next_cmd(char *prompt, FILE *fp);
void			freelist(char **list);
int				execute(t_sh *sh, char *argv[], int conn);
void			fatal(char *s1, char *s2, int n);
char			**parse(char *cmdl, t_sh *sh);
int				strlistlen(char **strlist);
int				redirection_read(char ***argv, int i);
int				redirection_append(char ***argv, int i);
int				redirection_append_err(char ***argv, int i);
int				redirection_write(char ***argv, int i);
int				redirection_error(char ***argv, int i);
char 			*redirection_parse(t_sh *sh, char *s);

#endif
