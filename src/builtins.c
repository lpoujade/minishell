/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 19:28:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/15 16:13:16 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_construct_path(t_env_item *env, char *av)
{
	char	*pwd;
	char	*tmp;

	(void)env;
	if (!(pwd = ft_strnew(PATH_MAX)))
		return (NULL);
	if (!(pwd = getcwd(pwd, PATH_MAX)))
		return (NULL);
	if (!access((tmp = ft_strjoin(pwd, av)), X_OK))
		return (tmp);
	return (NULL);
}

static char	*cd_get_path(t_env_item *env, char *av)
{
	char *fdir;
	char *oldpwd;

	fdir = NULL;
	if (!av)
		fdir = mgetenv(env, "HOME");
	else if (!ft_strcmp(av, "-"))
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
	char	**t;

	t = ft_strtnew(2);
	t[0] = ft_strdup("OLDPWD");
	t[1] = mgetenv(env, "PWD");
	if ((finaldir = cd_get_path(env, av[1])))
	{
		msetenv(env, t, NULL, 1);
		if (chdir(finaldir))
			return (-1);
		free(t[0]);
		free(t[1]);
		t[0] = ft_strdup("PWD");
		t[1] = finaldir;
		msetenv(env, t, NULL, 1);
	}
	ft_strtdel(&t);
	return (0);
}

int			builtins(t_shcmd *cmd, t_env_item *env)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strcmp(cmd->cmd, "cd"))
		bi_cd(cmd->args, env);
	else if (!ft_strcmp(cmd->cmd, "env"))
		menv(env, cmd->args + 1);
	else if (!ft_strcmp(cmd->cmd, "unsetenv"))
		munsetenv(&env, cmd->args[1]);
	else if (!ft_strcmp(cmd->cmd, "setenv"))
		msetenv(env, NULL, cmd->args[1], 1);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		myexit(&env, cmd->args[1] ? cmd->args[1] : "0", NULL);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_putendl((tmp = mgetenv(env, "PWD")));
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
