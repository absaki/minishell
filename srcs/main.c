/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:36:05 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/02 23:34:39 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// gcc -Wall -Wextra -Werror *.c -L. ../libft/libft.a -g -fsanitize=address

int		exec_builtin(char **args)
{
	int		result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(args);
	// if (ft_strcmp(args[0], "cd") == 0)
	// 	result = ft_cd(args, mini->env);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd();
	// if (ft_strcmp(args[0], "env") == 0)
	// 	ft_env(mini->env);
	// if (ft_strcmp(args[0], "export") == 0)
	// 	ft_export(args, mini->env, mini->secret_env);
	// if (ft_strcmp(args[0], "unset") == 0)
	// 	ft_unset(args, mini);
	return (result);
}

int		main(int argc, char **argv)
{
	char			*args[argc];
	int 			i;
	int				result;
	
	result = 0;
	i = 1;
	while (i < argc)
	{
		args[i - 1] = ft_strdup(argv[i]);
		i++;
	}
	if (argc > 1)
		result = exec_builtin(args);
	i = 0;
	// while (i < argc -1)
	// {
	// 	free(args[i]);
	// 	i++;
	// }
	return(argc);
}
