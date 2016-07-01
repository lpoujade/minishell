/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 01:49:14 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/25 02:54:30 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	**fill_nenv(char opts, char ***av)
{
	int		c;
	char	**new_env;
	char	**tmp;

	c = 0;
	new_env = NULL;
	tmp = NULL;
	if (opts == 'u' && !**av)
	{
		ft_putendl_fd("minishell: env: missing arg", 2);
		return (NULL);
	}
	while (environ[++c])
		;
	if (!(new_env = malloc(c * sizeof(char**))))
		return (NULL);
	c = 0;
	if (opts != 'i')
		while (environ[c])
		{
			if (opts != 'u' ||
					!cin_c2c(*(tmp = ft_strsplit(environ[c], "=")), *av))
				if (!(new_env[c] = ft_strdup(environ[c])))
					new_env[c] = NULL;
			if (tmp)
			{
				free(tmp[0]);
				free(tmp[1]);
				tmp[0] = NULL;
				tmp[1] = NULL;
				free(tmp);
				tmp = NULL;
			}
			c++;
		}

	new_env[c] = NULL;
	return (new_env);
}

static inline int	geto(char ***av)
{
	char opts;

	opts = 0;
	if (*av && **av && ***av == '-')
		if ((*(**av + 1) == 'u' || *(**av + 1) == 'i') && !*(**av + 2))
		{
			opts = *(**av + 1);
			(*av)++;
		}
	return (opts);
}

/*
** env launch a process with enventually modified actual env
** if no process, modified env is displayed
** env [-u NAME...]|[-i] [NAME=value] [cmd]
** -u delete NAMEs from env
** -i start from a void env
*/

int					bi_env(char **av)
{
	char	**new_env;
	int		c;
	char	opts;

	c = 0;
	opts = geto(&av);
	new_env = fill_nenv(opts, &av);
	while (*av && ((opts == 'u' && ft_isupper(**av)) || ft_strchr(*av, '=')))
		av++;
	if (!*av)
		while (new_env && new_env[c])
		{
			ft_putendl(new_env[c]);
			c++;
		}
	else
		command(*av, new_env, 0);
	if (new_env)
	{
		while (c + 1)
		{
			if (new_env[c])
				free(new_env[c]);
			c--;
		}
		free(new_env);
	}
	return (0);
}
