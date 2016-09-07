/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/01 21:06:05 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/07 14:57:11 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*mgetenv(t_env_item **env, int envcount, char *key)
{
	unsigned int	hash;
	t_env_item		*t;

	hash = chash(key, envcount);
	if (!env[hash])
		return (NULL);
	if (!ft_strcmp(key, env[hash]->key))
		return (env[hash]->value ? ft_strdup(env[hash]->value) : NULL);
	if (env[hash]->next)
	{
		t = env[hash];
		while (t && ft_strcmp(key, t->key))
			t = t->next;
		return (t ? ft_strdup(t->value) : NULL);
	}
	return (NULL);
}

t_env_item		*mgetenv_s(t_env_item **env, int envcount, char *key)
{
	unsigned int	hash;
	t_env_item		*t;

	hash = chash(key, envcount);
	if (!env[hash])
		return (NULL);
	if (!ft_strcmp(key, env[hash]->key))
		return (env[hash]);
	if (env[hash]->next)
	{
		t = env[hash];
		while (t && ft_strcmp(key, t->key))
			t = t->next;
		return (t ? t : NULL);
	}
	return (NULL);
}

char			**get_env_keys(t_env_item **env, int envcount)
{
	char		**ret;
	t_env_item	*t;
	int			hash;
	int			n;

	hash = 0;
	n = 0;
	if (!(ret = malloc(sizeof(char*) * envcount + 1)))
		return (NULL);
	while (hash < envcount)
	{
		if (env[hash])
		{
			if (!(ret[n] = ft_strdup(env[hash]->key)))
				return (NULL);
			n++;
			t = env[hash];
			while ((t = t->next))
				if (!(ret[n++] = ft_strdup(t->key)))
					return (NULL);
		}
		hash++;
	}
	ret[n] = NULL;
	return (ret);
}
