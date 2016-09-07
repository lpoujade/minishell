/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 19:28:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/07 13:35:09 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	bi_cd(char **av, t_env_item **env, int envcount)
{
	char *home;

	if (!av[1] && (home = mgetenv(env, envcount, "HOME")))
		chdir(home);
	else if (av[1])
	{
		if (!access(av[1], X_OK))
			chdir(av[1]);
		else if (!access(av[1], F_OK))
		{
			ft_putstr("bsh: cd: error for folder: ");
			ft_putendl(av[1]);
		}
		else
			ft_putendl_fd("No such directory", 2);
	}
	else
		ft_putendl("bsh: cd: error: no $HOME");
}

int			builtins(t_shcmd *cmd, t_env_item **env, int envcount)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strcmp(cmd->cmd, "cd"))
		bi_cd(cmd->args, env, envcount);
	else if (!ft_strcmp(cmd->cmd, "env"))
		!*(cmd->args + 1) ? print_env_strtable(env, envcount) : menv(env, envcount, cmd->args + 1);
	else if (!ft_strcmp(cmd->cmd, "getenv"))
		ft_putendl((tmp = mgetenv(env, envcount, cmd->args[1])));
	else if (!ft_strcmp(cmd->cmd, "unsetenv"))
		munsetenv(env, envcount, cmd->args[1]);
	else if (!ft_strcmp(cmd->cmd, "setenv"))
	{
		if (ft_strchr(cmd->args[1], '='))
		{
			if (!(msetenv(env, envcount, cmd->args[1])))
				return (-1);
		}
		else
			ft_putendl_fd("minishell: setenv: invalid parameter", 2);
	}
	else if (!ft_strcmp(cmd->cmd, "exit"))
		myexit(&env, envcount, (cmd->args[1] ? ft_atoi(cmd->args[1]) : 0), NULL);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_putendl((tmp = getcwd(NULL, 0)));
	else if (!ft_strcmp(cmd->cmd, "echo"))
		bi_echo(cmd->args + 1);
	else
		return (0);
	if (tmp)
		free(tmp);
	return (1);
}

void		bi_echo(char **args)
{
	int		c;

	c = 0;
	while (args[c])
	{
		ft_putstr(args[c]);
		ft_putchar(' ');
		c++;
	}
	ft_putchar('\n');
}
