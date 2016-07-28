/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 19:28:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/07/28 20:06:04 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basicshell.h"

static void	bi_cd(char **av)
{
	if (!av[1] && getenv("HOME"))
		chdir(getenv("HOME"));
	else if (av[1])
	{
		if (!access(av[1], X_OK))
			chdir(av[1]);
		else
		{
			ft_putstr("bsh: cd: error for folder: ");
			ft_putendl(av[1]);
			ft_putendl("bsh: defaut chdir to '/'");
			chdir("/");
		}
	}
	else
		ft_putendl("bsh: cd: error: no $HOME");
}

int			builtins(t_shcmd *cmd)
{
	int		echo_c;
	char	*tmp;

	echo_c = 0;
	if (!ft_strcmp(cmd->cmd, "cd"))
		bi_cd(cmd->args);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_putendl("bsh: env: not implemented yet");
	else if (!ft_strcmp(cmd->cmd, "setenv") || !ft_strcmp(cmd->cmd, "unsetenv"))
		ft_putendl("bsh: set/unset env: not implemented yet");
	else if (!ft_strcmp(cmd->cmd, "exit"))
		exit(cmd->args[1] ? ft_atoi(cmd->args[1]) : 0);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
	{
		ft_putendl((tmp = getcwd(NULL, 0)));
		free(tmp);
	}
	else if (!ft_strcmp(cmd->cmd, "echo"))
	{
		while (cmd->args[echo_c])
			ft_putstr(cmd->args[++echo_c] ? cmd->args[echo_c] : "\n");
	}
	else
		return (0);
	return (1);
}
