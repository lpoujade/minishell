/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 17:04:24 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/12 18:48:48 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		forkexec(char *cmd, char **av, t_env_item *env)
{
	pid_t	father;
	char	**tmp_env;
	int		ret_value;
	char	**ret2env;

	ret_value = 0;
	if ((father = fork()) < 0)
		exit(EXIT_FAILURE);
	if (!father)
	{
		if (!(tmp_env = env_to_table(env)))
			return (-1);
		if ((execve(cmd, av, tmp_env)))
			exit(EXIT_FAILURE);
	}
	if (father > 0)
	{
		ret2env = malloc(sizeof(char*) * 3);
		waitpid(father, &ret_value, 0);
		if (!ret2env)
			return (-1);
		ret2env[0] = ft_strdup("?");
		ret2env[1] = ft_itoa(WEXITSTATUS(ret_value));
		if (msetenv(env, ret2env, NULL, 1)) {
			ft_putendl("setenv error");
			return (-1);
		}
		free(ret2env[0]);
		free(ret2env[1]);
		free(ret2env);
	}
	return (ret_value);
}

int		exec_cmd(t_shcmd *cmd, t_env_item *env)
{
	char		*f;
	char		*path;

	f = NULL;
	path = NULL;
	if (!builtins(cmd, env))
	{
		if (!(path = mgetenv(env, "PATH")))
			ft_putendl("NO PATH");
		else if ((f = in_path(cmd->cmd, path)))
			forkexec(f, cmd->args, env);
		else
		{
			ft_putstr("minishell: command not found: ");
			ft_putendl(cmd->cmd);
		}
		if (f)
			free(f);
	}
	if (path)
		free(path);
	ft_strtdel(cmd->args);
	free(cmd->args);
	return (0);
}
