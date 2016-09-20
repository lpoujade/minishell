/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 14:36:02 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/20 10:26:15 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					env_fake_sort(t_list *t, t_list *n)
{
	(void)t;
	(void)n;
	return (1);
}

static t_env_item	*env_dup(t_env_item *env)
{
	t_env_item	*t;
	t_env_item	*tmp;
	t_env_item	*ne;

	if (!(t = env))
		return (NULL);
	ne = env_new_item(t->keyval, NULL, 1);
	while ((t = t->next))
	{
		tmp = env_new_item(t->keyval, NULL, 1);
		ft_lstappend((t_list*)ne, (t_list*)tmp);
	}
	return (ne);
}

static int			launch_cmd(t_env_item **e, t_env_item **new_e, char **av)
{
	char	*path;
	int		ret;
	t_shcmd	cmd;
	char	*cmd_path;

	ret = 0;
	path = NULL;
	cmd.cmd = *av;
	cmd.args = av;
	if (!builtins(&cmd, new_e))
	{
		path = mgetenv(*e, "PATH");
		if ((cmd_path = in_path(*av, path)))
			ret = forkexec(cmd_path, av, new_e);
		free(cmd_path);
		free(path);
	}
	if (path)
		path = ft_itoa(WEXITSTATUS(ret));
	else
		path = ft_strdup("127");
	msetenv(e, NULL, (cmd_path = ft_strjoin("?=", path)), 0);
	free(path);
	free(cmd_path);
	return (ret);
}

int					menv(t_env_item **env, char **args)
{
	t_env_item	*new_env;

	if (*args && !ft_strcmp(*args, "-i"))
	{
		new_env = NULL;
		args++;
	}
	else
		new_env = env_dup(*env);
	while (*args && ft_strchr(*args, '='))
		msetenv(&new_env, NULL, *args++, 1);
	if (*args)
		launch_cmd(env, &new_env, args);
	else
		env_print(new_env);
	env_free(&new_env);
	return (0);
}
