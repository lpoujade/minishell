/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 17:04:24 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/07 18:14:06 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		forkexec(char *cmd, char **av, t_env_item **env, int envcount)
{
	pid_t	father;
	char	**tmp_env;
	int		ret_value;

	ret_value = 0;
	if ((father = fork()) < 0)
		exit(EXIT_FAILURE);
	if (!father)
	{
		if (!(tmp_env = table_to_str(env, envcount)))
			return (-1);
		if ((execve(cmd, av, tmp_env)))
			exit(EXIT_FAILURE);
	}
	if (father > 0)
		waitpid(father, &ret_value, 0);
	if (ret_value)
	{
		ft_putstr("err");
		ft_putnbr(ret_value);
		ft_putchar(' ');
	}
	return (ret_value);
}

int		exec_cmd(t_shcmd *cmd, t_env_item **env, int envcount)
{
	char		*f;
	char		*path;

	f = NULL;
	path = NULL;
	if (!builtins(cmd, env, envcount))
	{
		if (!(path = mgetenv(env, envcount, "PATH")))
			ft_putendl("NO PATH");
		else if ((f = in_path(cmd->cmd, path)))
			forkexec(f, cmd->args, env, envcount);
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
