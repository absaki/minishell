/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:36:05 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/05 22:46:33 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// gcc -Wall -Wextra -Werror *.c -L. ../libft/libft.a -g -fsanitize=address

int		exec_builtin(t_sh *sh, char **args)
{
	int		result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(args, sh->env);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(args[0], "env") == 0)
		ft_env(sh->env);
	// if (ft_strcmp(args[0], "export") == 0)
	// 	ft_export(args, mini->env, mini->secret_env);
	// if (ft_strcmp(args[0], "unset") == 0)
	// 	ft_unset(args, mini);
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
	add_list_malloc(sh);
	return (sh);
}

int		main(int argc, char **argv, char **env_array)
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
	init_secret_env(sh, env_array);
	
	// for_debug
	// if (ft_strcmp(argv[1], "check_env") == 0)
	// {
	// 	while (sh->env->next)
	// 	{
	// 		printf("%s\n", sh->env->value);
	// 		sh->env = sh->env->next;
	// 	}
	// 	printf("\'%s\' ", sh->env->value);
	// }
	// if (ft_strcmp(argv[1], "check_secret_env") == 0)
	// {
	// 	while (sh->env->next)
	// 	{
	// 		printf("%s\n", sh->env->value);
	// 		sh->env = sh->env->next;
	// 	}
	// 	printf("\'%s\' ", sh->env->value);
	// }

	while (i < argc)
	{
		args[i - 1] = ft_strdup(argv[i]);
		i++;
	}
	args[i - 1] = NULL;
	if (argc > 1)
		result = exec_builtin(sh, args);
	i = 0;
	// while (i < argc -1)
	// {
	// 	free(args[i]);
	// 	i++;
	// }
	ft_lstclear(&g_list_malloc, free);
	return(argc);
}
