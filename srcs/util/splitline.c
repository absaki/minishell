/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:48:55 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/16 12:07:31 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_delim(char x)
{
	if (x == ' ' || x == '\t')
		return (1);
	return (0);
}

void	freelist(char **list)
{
	char **cp;

	cp = list;
	while (*cp)
		free(*cp++);
	free(list);
}

void	cmdread(char **buf, int *bufspace, int *pos)
{
	if (*pos + 1 >= *bufspace)
	{
		if (*bufspace == 0)
			*buf = malloc(BUFSIZ);
		else
			*buf = realloc(*buf, *bufspace + BUFSIZ);
		*bufspace += BUFSIZ;
	}
}

char	*next_cmd(char *prompt)
{
	char	*buf;
	char	status;

	ft_putstr_fd(prompt, STDERR);
	status = get_next_line(STDIN, &buf);
	if (status == 0)
	{
		ft_putendl_fd("exit", STDERR);
		return (NULL);
	}
	if (ft_strlen(buf) > 1024)
	{
		ft_putendl_fd("too long", 2);
		free(buf);
		buf = 0;
	}
	return (buf);
}
