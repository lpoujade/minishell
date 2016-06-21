/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/20 14:50:11 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/20 19:55:41 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*set_curpath(char **av)
{
	char	*curpath;
	char	*cdpaths;

	curpath = NULL;
	if (!*av)
		curpath = ft_strdup(getenv("HOME"));
	else if (**av == '-' && !*(*av + 1))
		(curpath = getenv("OLDPWD")) ? ft_putendl(curpath) : 0;
	else if (*av && (**av == '/' || (**av == '.' && (*(*av + 1) == '/' || !*(*av + 1) ||
						(*(*av + 1) == '.' && ((*(*av + 2) == '/') || !*(*av + 2)))))))
		curpath = *av;
	if (!curpath && *av && (**av != '-' || *(*av + 1)))
	{
		if (!access(*av, X_OK))
			curpath = *av;
		else if ((cdpaths = getenv("CDPATH")))
			ft_putendl((curpath = in_path(*av, cdpaths)) ? curpath
					: "cd: directory not accessible");
	}
	return (curpath);
}

static inline int	canon_form(char **path, char *ocurdir)
{
	char	*npath;
	char	*curdir;

	npath = NULL;
	if (!ocurdir)
		return (-1);
	curdir = ft_strjoin(ocurdir, "/");
	if (**path != '/')
		npath = ft_strjoin(curdir, *path);
	else
		npath = ft_strdup(*path);
	if (*npath != '/')
		ft_putendl("PATH NOT ABSOLUTE");
	if (ft_strstr(npath, "./") || ft_strstr(npath, "../"))
		ft_putendl("cleaning possible");
	free(curdir);
	return (0);
}

int					bi_cd(char **av)
{
	char	flag;
	char	*curpath;
	char	*oldpwd;

	flag = 0;
	curpath = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!*av && !getenv("HOME"))
		return (-1);
	if (ft_strlen(*av) == 2 && **av == '-')
		flag = ((*(*av + 1)) == 'P' || (*(*av + 1)) == 'L') ? *(*av + 1) : 0;
	if (!(curpath = set_curpath(flag ? av + 1 : av)))
		return (-1);
	if (flag != 'P')
		canon_form(&curpath, oldpwd);
	if (ft_strlen(curpath) > PATH_MAX)
		ft_putendl(">PATH_MAX");
	if (!access(curpath, X_OK) && chdir(curpath))
		ft_putendl("minishell: chdir fail");
	if (oldpwd)
	{
		setenv("OLDPWD", oldpwd, 1);
		free(oldpwd);
	}
	setenv("PWD", (oldpwd = getcwd(NULL, 0)), 1);
	free(oldpwd);
	if (!*av || (curpath != *av && (**av != '-' || *(*av + 1))))
		free(curpath);
	return (0);
}
