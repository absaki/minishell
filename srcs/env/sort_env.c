/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoi <kdoi@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:36:26 by kdoi              #+#    #+#             */
/*   Updated: 2021/02/06 19:44:24 by kdoi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_with_dquote(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '=' && str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	if (str[i] == '=')
	{
		write(1, &str[i++], 1);
		write(1, "\"", 1);
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
		}
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

int			get_len_of_tda(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void		sort_env_by_asc(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

size_t			size_len_of_env_value(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char			*convert_env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	if (!(env = malloc(sizeof(char) * size_len_of_env_value(lst) + 1)))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				i++;
				j++;
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

void		print_sorted_env(t_env *env)
{
	int		i;
	char	**tab;
	char	*str_env;

	str_env = convert_env_to_str(env);
	tab = ft_split(str_env, '\n');
	ft_free_and_del(str_env);
	sort_env_by_asc(tab, get_len_of_tda(tab));
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", 1);
		write_with_dquote(tab[i]);
		i++;
	}
	free_tda(tab);
}
