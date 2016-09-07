/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/hashlib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liums <lpoujade@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 15:11:19 by liums             #+#    #+#             */
/*   Updated: 2016/09/07 17:49:30 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Create initial table of t_env_items and set it to NULL
*/

static int		env_init(t_env_item ***f, char **environ)
{
	t_env_item	**final_env;
	int			env_items_count;
	int			c;

	c = 0;
	env_items_count = 0;
	while (environ && environ[env_items_count++])
		;
	if (!(final_env = malloc(sizeof(t_env_item*) * (env_items_count + 1))))
		return (-1);
	while (c < env_items_count)
		final_env[c++] = NULL;
	final_env[c] = NULL;
	*f = final_env;
	return (env_items_count);
}

/*
** add item on the specified hash, eventually after others
** items sharing the same hash
*/

int				add_item(char **keyval, t_env_item **env, int envcount,
		unsigned int hash)
{
	t_env_item *t;
	t_env_item *o;

	if (hash == 0)
		hash = chash(keyval[0], envcount);
	o = env[hash];
	if (!(t = malloc(sizeof(t_env_item))))
		return (-1);
	t->key = keyval[0];
	t->value = keyval[1];
	t->glob = 1;
	t->next = NULL;
	if (o)
	{
		while (o && o->next)
			o = o->next;
		o->next = t;
	}
	else
		env[hash] = t;
	return (0);
}

/*
** return a filled env hash table
*/

int				env_populate(t_env_item ***genv, char **environ)
{
	int			env_items_count;
	int			c;
	char		**keyval;
	int			hash;

	c = 0;
	env_items_count = env_init(genv, environ);
	while (environ && environ[c])
	{
		keyval = ft_strsplit(environ[c], "=");
		hash = chash(keyval[0], env_items_count);
		if (add_item(keyval, *genv, env_items_count, hash))
			return (-1);
		free(keyval);
		c++;
	}
	return (env_items_count);
}

/*
** Return a hash between 0 and max_hash for word
*/

unsigned int	chash(char *word, int max_hash)
{
	int				c;
	unsigned int	hash;

	hash = 0;
	c = 0;
	while (word[c])
	{
		hash = word[c] + (hash << 6) + (hash << 16) - hash;
		c++;
	}
	hash %= max_hash;
	return (hash);
}

char			**table_to_str(t_env_item **env, int envcount)
{
	char	**out_env;
	char	**env_keys;
	char	*tmp;
	int		c;

	c = 0;
	if (!(env_keys = get_env_keys(env, envcount)))
		return (NULL);
	if (!(out_env = malloc(sizeof(char**) * envcount + 1)))
		return (NULL);
	while (env_keys[c])
	{
		tmp = ft_strjoin(env_keys[c], "=");
		out_env[c] = ft_strjoin(tmp, mgetenv(env, envcount, env_keys[c]));
		free(tmp);
		free(env_keys[c]);
		c++;
	}
	free(env_keys);
	out_env[c] = NULL;
	return (out_env);
}
