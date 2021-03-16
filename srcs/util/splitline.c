/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:48:55 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/16 14:09:29 by kikeda           ###   ########.fr       */
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

int		my_getc(int	fd)
{
	char	c[1];
	int		status;

	status = read(fd, c, 1);
	if (status == -1)
		return (-1);
	if (status == 0)
		return (EOF);
	return ((int)c[0]);
}

char	*next_cmd(char *prompt)
{
	char	*buf;
	int		bufspace;
	int		pos;
	int		c;

	bufspace = 0;
	pos = 0;
	ft_putstr_fd(prompt, STDERR);
	while (1)
	{
		if ((c = my_getc(STDIN)) != EOF)
		{
			cmdread(&buf, &bufspace, &pos);
			if (c == '\n')
				break;
			buf[pos++] = c;
		}
		if (c == EOF && pos == 0)
		{
			ft_putendl_fd("exit", STDERR);
			return (NULL);
		}
	}
	buf[pos] = '\0';
	if(ft_strlen(buf) > 1024)
	{
		ft_putendl_fd("too long", 2);
		free (buf);
		buf = 0;
	}
	return (buf);
}
