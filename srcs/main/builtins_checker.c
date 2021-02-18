/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:36:05 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/19 01:34:23 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// gcc -Wall -Wextra -Werror *.c -L. ../libft/libft.a -g -fsanitize=address

int		exec_builtin(t_sh *sh, char **args)
{
	int		result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(args, sh);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(args[0], "env") == 0)
		ft_env(args, sh->env);
	if (ft_strcmp(args[0], "export") == 0)
		ft_export(args, sh->env, sh->senv);
	if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, sh);
	if (ft_strcmp(args[0], "exit") == 0)
	{
		ft_exit(sh ,args);
		printf("sh->ret: %d\n", sh->ret);//for_debug
		printf("sh->exit: %d\n", sh->exit);//for_debug
	}
	return (result);
}


t_sh	*make_new_sh(void)
{
	t_sh	*sh;

	sh = (t_sh *)malloc(sizeof(t_sh));
	if (!sh)
		return (NULL);
	sh->in = 0;
	sh->out = 0;
	sh->fdin = 0;
	sh->fdout = 0;
	sh->pipin = 0;
	sh->pipout = 0;
	sh->pid = 0;
	sh->charge = 0;
	sh->parent = 0;
	sh->last = 0;
	sh->ret = 0;
	sh->exit = 0;
	sh->no_exec = 0;
	sh->did_cd = 0;
	sh->unset_pwd = 0;
	sh->unset_oldpwd = 0;
	add_list_malloc(sh);
	return (sh);
}

int		builtin_checker(int argc, char **argv, char **env_array)
{
	char			*args[argc];
	int 			i;
	int				result;
	t_sh			*sh;

	
	result = 0;
	i = 1;
	if (!(sh = make_new_sh()))
	{
		printf("Error in make_new_sh\n");
		return(0);
	}
	init_env(sh, env_array);
	init_senv(sh, env_array);
	

	while (i < argc)
	{
		args[i - 1] = ft_strdup(argv[i]);
		i++;
	}
	args[i - 1] = NULL;
	if (argc > 1)
		result = exec_builtin(sh, args);
	i = 0;
	
	// for_debug
	if (ft_strcmp(argv[1], "check_env") == 0)
	{
		while (sh->env->next)
		{
			printf("%s\n", sh->env->vl);
			sh->env = sh->env->next;
		}
		printf("\'%s\' ", sh->env->vl);
	}
	if (ft_strcmp(argv[1], "check_senv") == 0)
	{
		while (sh->senv->next)
		{
			printf("%s\n", sh->senv->vl);
			sh->senv = sh->senv->next;
		}
		printf("\'%s\' ", sh->senv->vl);
	}
	if (ft_strcmp(argv[1], "export") == 0)
	{
		printf("\n\n========debug for export=========\n");
		printf("========env=========\n");
		while (sh->env->next)
		{
			printf("%s\n", sh->env->vl);
			sh->env = sh->env->next;
		}
		printf("\n========senv========\n");
		printf("\'%s\' ", sh->env->vl);
		while (sh->senv->next)
		{
			printf("%s\n", sh->senv->vl);
			sh->senv = sh->senv->next;
		}
		printf("\'%s\' ", sh->senv->vl);
	}
	if (ft_strcmp(argv[1], "unset") == 0)
	{
		printf("\n\n========debug for unset=========\n");
		printf("========env=========\n");
		while (sh->env->next)
		{
			printf("%s\n", sh->env->vl);
			sh->env = sh->env->next;
		}
		printf("\n========senv========\n");
		printf("\'%s\' ", sh->env->vl);
		while (sh->senv->next)
		{
			printf("%s\n", sh->senv->vl);
			sh->senv = sh->senv->next;
		}
		printf("\'%s\' ", sh->senv->vl);
	}
	if (ft_strcmp(argv[1], "cd") == 0)
	{
		printf("\n\n========debug for cd=========\n");
		printf("========env=========\n");
		while (sh->env->next)
		{
			printf("%s\n", sh->env->vl);
			sh->env = sh->env->next;
		}
		printf("\n========senv========\n");
		printf("\'%s\' ", sh->env->vl);
		while (sh->senv->next)
		{
			printf("%s\n", sh->senv->vl);
			sh->senv = sh->senv->next;
		}
		printf("\'%s\' ", sh->senv->vl);
	}
	
	ft_lstclear(&g_list_malloc, free);
	(void)result;
	return(argc);
}
