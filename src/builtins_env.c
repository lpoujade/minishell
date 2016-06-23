/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 01:49:14 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/23 05:20:36 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static inline char	**fill_nenv(char opts)
{
	int		c;
	char	**new_env;

	c = 0;
	new_env = NULL;
	while (environ[++c])
		;
	if (!(new_env = malloc(c * sizeof(char**))))
		return (NULL);
	c = 0;
	while (environ[c])
	{
		if (!(opts == 'i'))
			if (!(new_env[c] = ft_strdup(environ[c])))
				new_env[c] = NULL;
		c++;
	}
	new_env[c] = NULL;
	return (new_env);
}

/*
** env launch a process with enventually modified actual env
** if no process, env is displayed
** env [-u NAME] [NAME=value] [cmd]
** -u delete NAME
** -i clear env
*/

int					bi_env(char **av)
{
	char	**new_env;
	int		c;
	char	opts;
	char	*path;
	char	*cmd;

	c = 0;
	cmd = NULL;
	path = getenv("PATH");
	opts = geto(&av);
	new_env = fill_nenv(opts);
	if (!*av)
		while (new_env[c])
		{
			ft_putendl(new_env[c]);
			c++;
		}
	else if (in_builtins(av) == 404 && (!(access(*av, X_OK))
				|| (path && (cmd = in_path(*av, path)))))
		ft_putnbr(forkexec(cmd ? cmd : *av, av, (char**)environ));
	while (c + 1)
	{
		if (new_env[c])
			free(new_env[c]);
		c--;
	}
	if (cmd)
		free(cmd);
	free(new_env);
	return (0);
}

/*
**	{
**		while (av[c] && ft_strchr(av[c], '='))
**		{
**			while (new_env[i] &&
**					(ft_memcmp(new_env[i], av[c], ft_strclchr(av[c], '=')) ||
**					new_env[i][ft_strclchr(av[c], '=') + 1] == '='))
**				i++;
**			if (new_env[i])
**			{
**				free(new_env[i]);
**				new_env[i] = ft_strdup("nop=nop");
**			}
**			i = 0;
**			c++;
**		}
**		if (av[c])
**		{
**			ft_putendl(av[c]);
**			forkexec(av[c], (av + c + 1) ?: NULL, new_env);
**			ft_putendl("exec");
**		}
**		else
**		{
**			c = 0;
**			while (new_env[c])
**			{
**				ft_putendl(new_env[c]);
**				c++;
**			}
**		}
**	}
*/
