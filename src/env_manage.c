/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 19:23:58 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/07 13:46:08 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** create a single env item
*/

t_env_item	*env_create_item(char **keyval, int glob)
{
	t_env_item *t;

	if (!(t = malloc(sizeof(t_env_item))))
		return (NULL);
	t->key = keyval[0];
	t->value = keyval[1];
	t->glob = glob;
	t->next = NULL;
	return (t);
}

/*
** add item to env on hash
*/

int			env_add_item(t_env_item **env, int envcount, t_env_item *item)
{
	t_env_item		*t;
	t_env_item		*o;
	unsigned int	hash;

	hash = chash(item->key, envcount);
	if (!(t = malloc(sizeof(t_env_item))))
		return (-1);
	t->key = ft_strdup(item->key);
	t->value = ft_strdup(item->value);
	t->glob = item->glob;
	t->next = NULL;
	if (env[hash])
	{
		o = env[hash];
		while (o && o->next)
			o = o->next;
		o->next = t;
	}
	else
		env[hash] = t;
	return (0);
}

/*
** create new t_env_item table; fill it or not
*/

int			envdup(t_env_item **env, int envcount, t_env_item ***n)
{
	t_env_item	*t;
	int			hash;

	hash = 0;
	t = env[hash];
	if (!((*n) = malloc(sizeof(t_env_item*) * (envcount + 1))))
		return (-1);
	while (hash <= envcount)
		(*n)[hash++] = NULL;
	hash = 0;
	while (hash - 1 < envcount - 1)
	{
		if (!t)
		{
			while (!env[hash])
				hash++;
			t = env[hash++];
		}
		if (env_add_item((*n), envcount, t))
			return (-1);
		t = t->next;
	}
	return (envcount);
}

void		env_item_del(t_env_item **env, int hash)
{
	t_env_item *t;

	free(env[hash]->key);
	free(env[hash]->value);
	t = env[hash];
	if (env[hash]->next)
		env[hash] = env[hash]->next;
	else
		env[hash] = NULL;
	t->next = NULL;
	free(t);
	t = NULL;
}

int			envfree(t_env_item **env, int envcount)
{
	int			hash;

	hash = 0;
	while (hash <= envcount)
	{
		while (env[hash])
		{
			env_item_del(env, hash);
			if (--envcount < 0)
				return (1);
		}
		hash++;
	}
	return (0);
}
