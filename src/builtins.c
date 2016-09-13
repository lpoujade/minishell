/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 19:28:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/13 20:29:37 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_construct_path(t_env_item *env, char *av)
{
	char *fdir;
	char *oldpwd;

	fdir = NULL;
	if (!ft_strcmp(av, "-"))
	{
		oldpwd = mgetenv(env, "OLDPWD");
		ft_putendl(oldpwd);
		fdir = oldpwd;
	}
	else if (!access(av, X_OK))
		fdir = ft_strdup(av);
	else if (!access(av, F_OK))
	{
		ft_putstr("minishell: cd: error for folder: ");
		ft_putendl(av);
	}
	else
		ft_putendl_fd("No such directory", 2);
	return (fdir);
}

static int	bi_cd(char **av, t_env_item *env)
{
	char *finaldir;
	char *pwd;
	char *home;

	pwd = getcwd(NULL, 0);
	finaldir = NULL;
	if (!av[1] && (home = mgetenv(env, "HOME")))
		finaldir = home;
	else if (av[1])
		finaldir = cd_construct_path(env, av[1]);
	else
		ft_putendl("minishell: cd: error: no $HOME");
	if (finaldir)
	{
		if (chdir(finaldir))
			return (-1);
		free(finaldir);
	}
	/*
	msetenv_t(env, "OLDPWD", pwd);
	free(pwd);
	msetenv_t(env, "PWD", (pwd = getcwd(NULL, 0)));
	free(pwd);
	*/
	return (0);
}

int			builtins(t_shcmd *cmd, t_env_item *env)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strcmp(cmd->cmd, "cd"))
		bi_cd(cmd->args, env);
	else if (!ft_strcmp(cmd->cmd, "env"))
		;//menv(env, cmd->args + 1);
	else if (!ft_strcmp(cmd->cmd, "unsetenv"))
		;//munsetenv(&env, cmd->args[1]);
	else if (!ft_strcmp(cmd->cmd, "setenv"))
		msetenv(env, NULL, cmd->args[1], 1);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		myexit(&env, cmd->args[1] ? cmd->args[1] : "0", NULL);
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
