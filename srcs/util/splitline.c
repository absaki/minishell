/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:48:55 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/16 14:44:35 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				freelist(char **list)
{
	char **cp;

	cp = list;
	while (*cp)
		free(*cp++);
	free(list);
}

static void			*my_reallocf(void *ptr, size_t oldsize, size_t size)
{
	void	*new;

	new = malloc(size);
	if (new == NULL)
		no_mem();
	memcpy(new, ptr, oldsize);
	free(ptr);
	return (new);
}

static void			cmdread(char **buf, int *bufspace, int *pos)
{
	if (*pos + 1 >= *bufspace)
	{
		if (*bufspace == 0)
			*buf = my_malloc(BUFSIZ);
		else
			*buf = my_reallocf(*buf, *bufspace,*bufspace + BUFSIZ);
		*bufspace += BUFSIZ;
	}
}

static int			my_getc(int fd)
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

char				*next_cmd(char *prompt)
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
				break ;
			buf[pos++] = c;
		}
		if (c == EOF && pos == 0)
		{
			ft_putendl_fd("exit", STDERR);
			return (NULL);
		}
	}
	buf[pos] = '\0';
	return (buf);
}
