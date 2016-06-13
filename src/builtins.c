/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 12:24:23 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/13 20:44:54 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		bi_cd(char **av)
{
	int		c;
	char	*oldpwd;
	char	*npath;

	c = 0;
	oldpwd = NULL;
	if (getenv("OLDPWD"))
		oldpwd = ft_strdup(getenv("OLDPWD"));
	if ((npath = getcwd(NULL, 0)))
	{
		free(npath);
		setenv("OLDPWD", npath, 1);
	}
	npath = NULL;
	if (!*av)
		   npath = getenv("HOME");
	else if (**av == '-' && oldpwd)
	{
		npath = oldpwd;
		ft_putendl(oldpwd);
	}
	else if (*av)
	{
		if ((!(access(*av, X_OK))))
			npath = *av;
		else
			ft_putendl("cd: Directory not accessible");
	}
	if (npath && *npath)
		chdir(npath);
	else
		return (-1);
	free(oldpwd);
	return (0);
}

/*
** env launch a process with enventually modified actual env
** if no process, env is displayed
** env [-u NAME] [NAME=value] [cmd]
** -u delete NAME
** -i clear env
*/

int		env(char **av)
{
	int	c;

	c = 0;
	if (!*av)
		while (*(environ + c))
			ft_putendl(*(environ + c++));
	else if (*((*av) + 1) == 'i')
	{
		ft_putendl(*(av + 2));
		forkexec(*(av + 2), (av + 3) ? av + 3 : NULL);
	}
	else if (*((*av) + 1) == 'u')
	{
		if (!*(av + 1))
			ft_putendl("which one ?");
		else if (unsetenv(*(av + 1)))
			ft_putendl("env: error");
	}
	else
	{
		if (!*(av + 1))
			ft_putendl("USAGE");
		else if (setenv(*av, *(av + 1), 1))
			perror("minishell: env()");
	}
	return (0);
}
