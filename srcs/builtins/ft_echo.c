/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:48:41 by kdoi              #+#    #+#             */
/*   Updated: 2021/03/06 16:44:28 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_argv_n_option(char *argv)
{
	char	*substr;
	int		i;

	if (ft_strncmp(argv, "-n", 2) == 0)
	{
		substr = ft_substr(argv, 2, ft_strlen(argv));
		i = 0;
		while (substr[i])
		{
			if (substr[i] != 'n')
				break ;
			i++;
		}
		if (substr[i] == '\0')
		{
			free(substr);
			return (1);
		}
		free(substr);
	}
	return (0);
}

static int	cnt_n_option(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_argv_n_option(argv[i]) == 1)
			i++;
		else
			break ;
	}
	return (i);
}

int			ft_echo(char *argv[])
{
	int	i;

	if (argv[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	i = cnt_n_option(argv);
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], 1);
		if (argv[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (is_argv_n_option(argv[1]) == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
