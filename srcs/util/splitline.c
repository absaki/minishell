/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 15:48:55 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/14 23:20:31 by kikeda           ###   ########.fr       */
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

char	*next_cmd(char *prompt, FILE *fp)
{
	char	*buf;
	int		bufspace;
	int		pos;
	int		c;

	bufspace = 0;
	pos = 0;
	ft_putstr_fd(prompt, STDERR);
	// printf("%s", prompt);
	while ((c = getc(fp)) != EOF)
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
	buf[pos] = '\0';
	if(ft_strlen(buf) > 1024)
	{
		ft_putendl_fd("too long", 2);
		free (buf);
		buf = 0;
	}
	return (buf);
}
