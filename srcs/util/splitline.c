/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:48:55 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/20 23:48:34 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				freelist(char **list)
{
	int		i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
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

static int			cmdread(char **buf, int *bufspace, int *pos)
{
	if (*pos + 1 >= *bufspace)
	{
		if (*bufspace == 0)
			*buf = my_malloc(BUFSIZ);
		else
			*buf = my_reallocf(*buf, *bufspace, *bufspace + BUFSIZ);
		*bufspace += BUFSIZ;
	}
	return (SUCCESS);
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

char				*next_cmd(void)
{
	char	*buf;
	int		bufspace;
	int		pos;
	int		c;

	bufspace = 0;
	pos = 0;
	while (1)
	{
		if (g_sig.sigint)
			sigint_reset(&buf, &pos);
		else if ((c = my_getc(STDIN)) != EOF && cmdread(&buf, &bufspace, &pos))
		{
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
