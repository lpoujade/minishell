/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 12:24:23 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/19 17:04:56 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*set_curpath(char **av)
{
	char	*curpath;

	curpath = NULL;
	if (!*av)
		curpath = getenv("HOME");
	else if (**av == '-' && !*(*av + 1))
		(curpath = getenv("OLDPWD")) ? ft_putendl(curpath) : 0;
	else if (*av && (**av == '/' ||
				(**av == '.' && (!*(*av + 1) || *(*av + 1) == '.'))))
		curpath = *av;
	if (!curpath && *av && (**av != '-' || *(*av + 1)))
		curpath = *av;
	return (curpath);
}

int					bi_cd(char **av)
{
	short	flag;
	char	*curpath;
	char	*oldpwd;

	flag = 0;
	curpath = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!*av && !getenv("HOME"))
		return (-1);
	if (*av && **av == '-' && (*(*av + 1) == 'P' || *(*av + 1) == 'L') &&
			!*(*av + 2))
		flag = *(*av + 1);
	curpath = set_curpath(flag ? av + 1 : av);
	if (chdir(curpath))
		ft_putendl("directory inaccessible");
	setenv("OLDPWD", oldpwd, 1);
	free(oldpwd);
	setenv("PWD", (oldpwd = getcwd(NULL, 0)), 1);
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

int					bi_env(char **av)
{
	int	c;

	c = 0;
	if (!*av)
		while (*(environ + c))
		{
			ft_putendl(*(environ + c));
			c++;
		}
	else if (**av == '-' && **(av + 1) == 'u')
		;
	else if (**av == '-' && *(*av + 1) == 'i' && *(av + 1))
		forkexec(*(av + 1), (av + 1), NULL);
	else if (**av == '-' && **(av + 1) == 'i')
		;
	return (0);
}

int					bi_suenv(char **av)
{
	int	c;

	c = 0;
	if (!*av)
		return (-1);
	else if (**av == 's' && *(av + 1))
	{
		if (setenv(*(av + 1), ft_strchr(*(av + 1), '='), 1))
			ft_putendl("env: error");
	}
	else if (**av == 'u')
	{
		if (*(av + 1) && unsetenv(*(av + 1)))
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
