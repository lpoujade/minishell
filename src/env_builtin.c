/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 14:36:02 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/15 17:01:43 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_item	*env_dup(t_env_item *env)
{
	t_env_item	*t;
	t_env_item	*tmp;
	t_env_item	*ne;

	t = env;
	ne = env_new_item(t->keyval, NULL, 1);
	while ((t = t->next))
	{
		tmp = env_new_item(t->keyval, NULL, 1);
		ft_lstappend((t_list*)ne, (t_list*)tmp);
	}
	return (ne);
}

int					menv(t_env_item *env, char **args)
{
	t_env_item	*new_env;
	char		*cmd;
	char		*path;
	int			ret;

	ret = 0;
	if (*args && !ft_strcmp(*args, "-i"))
	{
		new_env = env_new_item(NULL, "S=minishell", 0);
		args++;
	}
	else if (!(new_env = env_dup(env)))
		return (-1);
	while (*args && ft_strchr(*args, '='))
	{
		msetenv(new_env, NULL, *args, 1);
		args++;
	}
	if (*args)
	{
		path = mgetenv(env, "PATH");
		cmd = in_path(*args, path);
		ret = forkexec(cmd, args, new_env);
		free(cmd);
		free(path);
	}
	else
		env_print(new_env);
	env_free(&new_env);
	return (ret);
}
