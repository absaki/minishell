/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:48:31 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/12 16:55:04 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	substrend(char **str, int rstart, int rend)
{
	char *new;
	int oldlen;
	int i;
	int j;

	oldlen = ft_strlen(*str);
	if (rend < rstart || oldlen <= rstart || oldlen <= rend)
		return (ERROR);
	if ((new = malloc(oldlen - (rend - rstart))) == NULL)
		no_mem();
	i = 0;
	j = 0;
	while ((*str)[i] && i < rstart)
		new[j++] = (*str)[i++];
	printf("first break i = %d, j = %d\n", i,j);
	if (i == rstart)
		i = rend + 1;
	while ((*str)[i])
		new[j++] = (*str)[i++];
	new[j] = '\0';
	printf("rstart = %d, rend = %d old = \"%s\"  new = \"%s\"\n", rstart, rend, *str, new);
	free(*str);
	*str = new;
	return (SUCCESS);
}

void	rd_free(t_redirection *rd)
{
	free(rd->file);
	free(rd);
}
