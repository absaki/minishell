/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:34:02 by kikeda            #+#    #+#             */
/*   Updated: 2021/02/28 23:22:59 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int replase_var(char *s, t_sh *sh, char **tmp)
// {
// }

int dollar_without_parenthesis(char *s, t_sh *sh, char **tmp)
{
	int i;
	int end;
	char *new;
	char *cpy;

	i = 1;
	while (s[i] && ft_isalnum(s[i]))
		i++;
	if(i == 1)
		return (joinlast_onechr('$', tmp));
	end = i;
	if ((cpy = malloc(sizeof(char) * end)) == NULL)
		no_mem();
	i = 0;
	while (i + 1 < end)
	{
		cpy[i] = s[i + 1];
		i++;
	}
	cpy[i] = '\0';
	if ((new = ft_strjoin(*tmp, get_env_value(cpy, sh->env))) == NULL)
		no_mem();
	free(cpy);
	free(*tmp);
	*tmp = new;
	return (end);
}

int dollar_with_parenthesis(char *s, t_sh *sh, char **tmp)
{
	int i;
	int end;
	char *new;
	char *cpy;

	i = 1;
	while (s[i] && s[i] != '}')
		i++;
	if(i == 2)
		return (3);
	end = i;
	if ((cpy = malloc(sizeof(char) * end)) == NULL)
		no_mem();
	i = 0;
	while (i + 2 < end)
	{
		cpy[i] = s[i + 2];
		i++;
	}
	cpy[i] = '\0';
	if ((new = ft_strjoin(*tmp, get_env_value(cpy, sh->env))) == NULL)
		no_mem();
	free(cpy);
	free(*tmp);
	*tmp = new;
	return (end + 1);
}

int dollar(char *s, t_sh *sh, char **tmp)
{
	if (!s[1])
		return (joinlast_onechr('$', tmp));
	if (!ft_strncmp(s, "$\"\"", 3))
		return (3);
	if (!ft_strncmp(s, "$\'\'", 3))
		return (3);
	if (s[1] && s[1] == '{')
		return (dollar_with_parenthesis(s, sh, tmp));
	if (*(s + 1))
		return (dollar_without_parenthesis(s, sh, tmp));
	return (1);
}

int s_quote(char *s, char **tmp)
{
	int i;
	int end;
	char *new;
	char *cpy;

	i = 1;
	while (s[i] && s[i] != '\'')
		i++;
	end = i;
	if ((cpy = malloc(sizeof(char) * end)) == NULL)
		no_mem();
	i = 0;
	while (s[i + 1] && s[i + 1] != '\'')
	{
		cpy[i] = s[i + 1];
		i++;
	}
	cpy[i] = '\0';
	if ((new = ft_strjoin(*tmp, cpy)) == NULL)
		no_mem();
	free(cpy);
	free(*tmp);
	*tmp = new;
	return (i + 2);
}

int d_quote(char *s, t_sh *sh, char **tmp)
{
	int i;

	i = 1;
	while (s[i] != '\"')
	{
		if (s[i] && s[i] == '$')
			i += dollar(&(s[i]), sh, tmp);
		else if (s[i])
			i += joinlast_onechr(s[i], tmp);
	}
	return (i + 1);
}

int join_arglist(char **tmp, char ***args, char *s)
{
	int i;
	int len;
	char **rtn;

	i = 0;
	while ((*args)[i])
		i++;
	len = i;
	if ((rtn = (char **)malloc(sizeof(char *) * (len + 2))) == 0)
		no_mem();
	i = 0;
	while ((*args)[i])
	{
		if ((rtn[i] = ft_strdup((*args)[i])) == NULL)
			no_mem();
		i++;
	}
	freelist(*args);
	if ((rtn[i] = ft_strdup(*tmp)) == NULL)
		no_mem();
	free(*tmp);
	*tmp = malloc(sizeof(char) * 1);
	(*tmp)[0] = 0;
	i++;
	rtn[i] = NULL;
	*args = rtn;
	i = 0;
	while (s[i] == ' ')
		i++;
	return (i);
}

char **split_args(char *s, t_sh *sh)
{
	char **rtn;
	char *tmp;
	int i;

	i = 0;
	rtn = malloc(sizeof(char *));
	rtn[0] = 0;
	tmp = malloc(sizeof(char));
	tmp[0] = 0;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == ' ')
			i += join_arglist(&tmp, &rtn, &s[i]);
		else if (s[i] == '\'')
			i += s_quote(&s[i], &tmp);
		else if (s[i] == '\"')
			i += d_quote(&s[i], sh, &tmp);
		else if (s[i] == '$')
			i += dollar(&s[i], sh, &tmp);
		else
			i += joinlast_onechr(s[i], &tmp);
	}
	if (tmp[0])
		join_arglist(&tmp, &rtn, &s[i]);
	i = 0;
	// while(rtn[i])
	// {
	// 	printf("arg[%d]->%s<-\n", i, rtn[i]);
	// 	i++;
	// }
	return (rtn);
}
