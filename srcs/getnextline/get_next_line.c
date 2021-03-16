/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:07:22 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/16 12:07:13 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_2(void *ptr1, void *ptr2)
{
	free(ptr1);
	free(ptr2);
	return (-1);
}

int		dup_output(char **line, char **buf)
{
	char *output;
	char *buf_tmp;
	char *p_newline;

	if (*buf)
	{
		buf_tmp = ft_strjoin(*buf, "");
		free(*buf);
	}
	else
		buf_tmp = ft_strjoin("", "");
	if ((p_newline = ft_strchr(buf_tmp, '\n')))
	{
		output = ft_substr(buf_tmp, 0, (p_newline - buf_tmp));
		if (output == NULL)
			return (free_2(buf_tmp, NULL));
		*line = output;
		*buf = ft_substr(p_newline, 1, ft_strlen(p_newline));
		free(buf_tmp);
		return (*buf ? 1 : -1);
	}
	*line = buf_tmp;
	*buf = NULL;
	return (buf_tmp ? 0 : -1);
}

int		buf_set(char *tmp, char **buf, int num_read)
{
	char *buf_str;

	if (num_read == -1)
		return (-1);
	tmp[num_read] = '\0';
	if (!(buf_str = ft_strjoin((*buf ? *buf : ""), tmp)))
		return (-1);
	if (*buf)
		free(*buf);
	*buf = buf_str;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*buf[256];
	char		*tmp;
	int			num_read;

	if (fd < 0 || line == NULL || !(tmp = malloc(1024 + 1)))
		return (-1);
	while (1)
	{
		num_read = read(fd, tmp, 1024);
		if (buf_set(tmp, &buf[fd], num_read) == -1)
			return (free_2(buf[fd], tmp));
		if (num_read == -1)
			return (free_2(buf[fd], tmp));
		if (num_read < 1024 || ft_strchr(tmp, '\n'))
			break ;
	}
	free(tmp);
	return (dup_output(line, &buf[fd]));
}
