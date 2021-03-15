/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:09:27 by kikeda            #+#    #+#             */
/*   Updated: 2021/03/15 13:19:46 by kikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_without_parenthesis(char *s, t_sh *sh, char **tmp, int trim)
{
	int		i;
	int		end;
	char	*new;
	char	*cpy;

	i = 1;
	while (s[i] && ((ft_isalnum(s[i])) || s[i] == '_'))
		i++;
	if (i == 1)
		return (joinlast_onechr('$', tmp));
	end = i;
	cpy = my_malloc(sizeof(char) * end);
	i = 0;
	while (i + 1 < end)
	{
		cpy[i] = s[i + 1];
		i++;
	}
	cpy[i] = '\0';
	new = freeable_strjoin(*tmp, get_env_value(cpy, sh->env), 1, 1);
	free(cpy);
	*tmp = new;
	dollar_trim(trim, tmp);
	return (end);
}

static int	dollar_with_parenthesis(char *s, t_sh *sh, char **tmp, int trim)
{
	int		i;
	int		end;
	char	*new;
	char	*cpy;

	i = 1;
	while (s[i] && s[i] != '}')
		i++;
	if (i == 2)
		return (3);
	end = i;
	cpy = my_malloc(sizeof(char) * end);
	i = 0;
	while (i + 2 < end)
	{
		cpy[i] = s[i + 2];
		i++;
	}
	cpy[i] = '\0';
	new = freeable_strjoin(*tmp, get_env_value(cpy, sh->env), 1, 1);
	free(cpy);
	*tmp = new;
	dollar_trim(trim, tmp);
	return (end + 1);
}

static int	dollar_question_with_parenthesis(char **tmp)
{
	char *new;
	char *oldstr;

	if ((new = ft_itoa(g_sig.status)) == NULL)
		no_mem();
	oldstr = *tmp;
	if ((*tmp = ft_strjoin(oldstr, new)) == NULL)
		no_mem();
	free(oldstr);
	return (4);
}

static int	dollar_question_without_parenthesis(char **tmp)
{
	char *new;
	char *oldstr;

	if ((new = ft_itoa(g_sig.status)) == NULL)
		no_mem();
	oldstr = *tmp;
	if ((*tmp = ft_strjoin(oldstr, new)) == NULL)
		no_mem();
	free(oldstr);
	return (2);
}

int			dollar(char *s, t_sh *sh, char **tmp, int trim)
{
	if (!s[1])
		return (joinlast_onechr('$', tmp));
	if (!ft_strncmp(s, "$\"\"", 3))
		return (3);
	if (!ft_strncmp(s, "$\'\'", 3))
		return (3);
	if (!ft_strncmp(s, "$?", 2))
		return (dollar_question_without_parenthesis(tmp));
	if (!ft_strncmp(s, "${?}", 4))
		return (dollar_question_with_parenthesis(tmp));
	if (s[1] && s[1] == '{')
		return (dollar_with_parenthesis(s, sh, tmp, trim));
	if (*(s + 1))
		return (dollar_without_parenthesis(s, sh, tmp, trim));
	return (1);
}
