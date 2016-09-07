/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 15:32:43 by liums             #+#    #+#             */
/*   Updated: 2016/09/07 11:57:50 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	print_env(t_env_item **env, int envcount)
{
	t_env_item	*t;
	int			hash;
	int			n;

	hash = 0;
	n = 0;
	t = env[hash];
	while (hash < envcount)
	{
		if (env[hash])
		{
			ft_putstr(env[hash]->key);
			ft_putchar('=');
			ft_putendl(env[hash]->value);
			t = env[hash];
			while ((t = t->next))
			{
				ft_putstr(t->key);
				ft_putchar('=');
				ft_putendl(t->value);
			}
		}
		hash++;
	}
}

void	print_env_strtable(t_env_item **env, int envcount)
{
	char	**str_env;
	int		c;

	c = 0;
	if (!(str_env = table_to_str(env, envcount)))
	{
		ft_putendl("NO RETURN FROM table_to_str()");
		return ;
	}
	while (str_env[c])
	{
		ft_putendl(str_env[c]);
		free(str_env[c]);
		c++;
	}
	free(str_env);
}
