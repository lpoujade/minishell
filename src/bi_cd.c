/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 11:47:38 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/20 14:34:50 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_clean(char *path)
{
	char	*tmp;
	char	*prev;
	char	*buf;

	if (!(buf = ft_strnew(PATH_MAX)))
		return (NULL);
	tmp = path + 1;
	while (tmp)
	{
		if (*tmp == '.' && *(tmp + 1) == '.'
				&& ((*(tmp + 2) == '/')	|| !*(tmp + 2)))
		{
			ft_putendl(path);
			buf = ft_strndup(prev, (tmp - prev) + (*(tmp + 2) ? 3 : 2));
			path = ft_strrmstr(path, buf);
			ft_putendl(path);
		}
		prev = tmp;
		if ((tmp = ft_strchr(tmp, '/')))
			tmp += 1;
	}
	return (path);
}

static char	*cd_construct_path(char *av)
{
	char	*pwd;
	char	*tmp;
	char	*ret;

	ret = NULL;
	if (*av == '/')
		return (path_clean(av));
	if (!(pwd = ft_strnew(PATH_MAX)))
		return (NULL);
	if (!(pwd = getcwd(pwd, PATH_MAX)))
		return (NULL);
	ft_strcat(pwd, "/");
	if (!access((tmp = ft_strjoin(pwd, av)), X_OK))
		ret = tmp;
	free(pwd);
	return (path_clean(ret));
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
	else
		fdir = cd_construct_path(av);
	return (fdir);
}

int			bi_cd(char **av, t_env_item *env)
{
	char	*finaldir;
	char	**t;

	t = ft_strtnew(2);
	t[0] = ft_strdup("OLDPWD");
	t[1] = mgetenv(env, "PWD");
	if ((finaldir = cd_get_path(env, av[1])))
	{
		msetenv(&env, t, NULL, 1);
		if (chdir(finaldir))
			return (-1);
		free(t[0]);
		free(t[1]);
		t[0] = ft_strdup("PWD");
		t[1] = finaldir;
		msetenv(&env, t, NULL, 1);
	}
	ft_strtdel(&t);
	return (0);
}

