/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 15:37:42 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/12 18:54:35 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_item		*env_new_item(char **keyval, char *keyval_in_one, int g)
{
	t_env_item	*n;
	int			c;

	n = NULL;
	c = 0;
	if (!(n = malloc(sizeof(t_env_item))) || !(n->keyval = malloc(sizeof(char*) * 3)))
		return (NULL);
	if (keyval_in_one)
	{
		if (!(keyval = ft_strsplit(keyval_in_one, "=")))
			return (NULL);
		c = 1;
	}
	n->keyval[0] = ft_strdup(keyval[0]);
	n->keyval[1] = ft_strdup(keyval[1]);
	n->keyval[2] = NULL;
	n->next = NULL;
	n->prev = NULL;
	n->glob = g;
	if (c)
	{
		ft_strtdel(keyval);
		free(keyval);
	}
	return (n);
}

int				env_populate(t_env_item **env, char **environ)
{
	int			c;
	t_env_item	*item;

	c = 0;
	while (environ && environ[c])
	{
		item = env_new_item(NULL, environ[c], 1);
		if (!*env)
			*env = item;
		else
			ft_lstinsert((t_list**)env, (t_list*)item, &env_fake_sort);
		c++;
	}
	return (0);
}

static void		env_del_one(void *t)
{
	t_env_item *item;

	item = (t_env_item*)t;
	ft_strtdel(item->keyval);
	free(item->keyval);
	item->keyval = NULL;
}

void			env_free(t_env_item **env)
{
	ft_lstdel((t_list**)env, &env_del_one);
	if (*env)
	{
		free(*env);
		*env = NULL;
	}
}

int				env_fake_sort(t_list *t, t_list *n)
{
	(void)t;
	(void)n;
	return (1);
}

void			env_print(t_env_item *env)
{
	ft_lstiter((t_list*)env, &env_print_node);
}

void			env_print_node(t_list *m)
{
	t_env_item *n;
	char	*s;

	n = (t_env_item*)m;
	if (!(s = ft_strnew(ft_strlen(n->keyval[0]) + ft_strlen(n->keyval[1]) + 1)))
	{
		ft_putendl_fd("ERROR env_print_node", 2);
		return ;
	}
	ft_strcat(s, n->keyval[0]);
	ft_strcat(s, "=");
	ft_strcat(s, n->keyval[1]);
	ft_putendl(s);
	free(s);
}

char		*mgetenv(t_env_item *env, char *key)
{
	t_env_item *t;

	t = env;
	while (t && ft_strcmp(t->keyval[0], key))
		t = t->next;
	return (t ? ft_strdup(t->keyval[1]) : NULL);
}

char		**env_to_table(t_env_item *env)
{
	char		**new_env;
	t_env_item	*t;
	int			c;

	c = 0;
	t = env;
	while((t = t->next))
		c++;
	t = env;
	if (!(new_env = malloc(sizeof(char*) * (c + 1))))
		return (NULL);
	c = 0;
	while (t)
	{
		new_env[c] = ft_strjoin(t->keyval[0], ft_strjoin("=", t->keyval[1]));
		c++;
		t = t->next;
	}
	new_env[c] = NULL;
	return (new_env);
}

int			msetenv(t_env_item *env, char **keyval, char *pair, int g)
{
	t_env_item *t;
	t_env_item *a;
	t_env_item *bcp;

	a = env;
	t = env_new_item(keyval, pair, g);
	while (a && ft_strcmp(a->keyval[0], t->keyval[0]))
	{
		bcp = a,
		a = a->next;
	}
	if (a)
	{
		free(a->keyval[1]);
		a->keyval[1] = ft_strdup(t->keyval[1]);
		env_del_one(t);
		free(t);
		t = NULL;
	}
	else
	{
		bcp->next = t;
		t->prev = bcp;
	}
	return (0);
}
