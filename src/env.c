/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 19:29:05 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/11 13:21:35 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_for_env(t_env_item **env, int envcount, char **args)
{
	t_env_item	*tmp;
	char		**keyval;
	int			c;

	c = 0;
	while (*args && ft_strchr(*args, '='))
	{
		keyval = ft_strsplit(*args, "=");
		env_add_item(env, envcount, (tmp = env_create_item(keyval, 1)));
		ft_strtdel(keyval);
		free(keyval);
		free(tmp);
		args++;
		c++;
	}
	return (c);
}

int		menv(t_env_item **env, int envcount, char **args)
{
	t_env_item	**new_env;
	char		*cmd;
	char		*path;
	int			new_envcount;
	int			ret;

	ret = 0;
	new_envcount = envcount;
	if (*args && !ft_strcmp(*args, "-i"))
	{
		if (!(new_env = malloc(sizeof(t_env_item*) * envcount)))
			return (-1);
		while (envcount)
			new_env[--envcount] = NULL;
		envcount = new_envcount;
		args++;
	}
	else if ((new_envcount = envdup(env, envcount, &new_env)) < 0)
	{
		ft_putendl("bad return");
		return (-1);
	}
	args += parse_for_env(new_env, new_envcount, args);
	if (*args)
	{
		cmd = in_path(*args, (path = mgetenv(env, envcount, "PATH")));
		ret = forkexec(cmd, args, new_env, new_envcount);
		free(cmd);
		free(path);
	}
	else
		print_env(new_env, new_envcount);
	envfree(new_env, new_envcount);
	return (ret);
}

int		msetenv(t_env_item **env, int envcount, char *keyval)
{
	t_env_item	*t;
	char		**item;

	if (!(item = ft_strsplit(keyval, "=")))
		return (-1);
	if (!(t = mgetenv_s(env, envcount, item[0])))
	{
		ft_putendl_fd("minishell: adding item to env not implemented", 2);
		return (-1);
	}
	free(t->value);
	t->value = item[1];
	free(item[0]);
	free(item);
	return (0);
}

int		msetenv_t(t_env_item **env, int envcount, char *key, char *val)
{
	t_env_item	*t;

	if (!(t = mgetenv_s(env, envcount, key)))
	{
		ft_putendl_fd("minishell: adding item to env not implemented", 2);
		return (-1);
	}
	free(t->value);
	t->value = ft_strdup(val);
	return (0);
}

int		munsetenv(t_env_item **env, int envcount, char *key)
{
	t_env_item *t;

	t = mgetenv_s(env, envcount, key);
	if (t->value)
		free(t->value);
	t->value = NULL;
	return (0);
}
