/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 11:47:38 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/21 17:54:03 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_clean(char *path)
{
	char	*tmp;
	char	*prev;
	char	*buf;
	char	*t;

	tmp = path + 1;
	buf = NULL;
	while (tmp)
	{
		if (*tmp == '.' && *(tmp + 1) == '.'
				&& ((*(tmp + 2) == '/') || !*(tmp + 2)))
		{
			buf = ft_strndup(prev, (tmp - prev) + (*(tmp + 2) ? 3 : 2));
			t = ft_strrmstr(path, buf);
			free(path);
			path = t;
			free(buf);
			buf = NULL;
		}
		else if (*tmp == '.' && (!*(tmp + 1) || *(tmp + 1) == '/'))
		{
			t = ft_strrmstr(path, tmp);
			free(path);
			path = t;
		}
		prev = tmp;
		if ((tmp = ft_strchr(tmp, '/')))
			tmp += 1;
	}
	if (buf)
		free(buf);
	return (path);
}

static char	*cd_construct_path(t_env_item *env, char *av)
{
	char	*pwd;
	char	*tmp;
	char	*ret;

	if (*av == '/')
		return (!access(av, X_OK) ? path_clean(ft_strdup(av)) : NULL);
	if (!(pwd = ft_strnew(PATH_MAX)))
		return (NULL);
	if (!(tmp = mgetenv(env, "PWD")))
	{
		free(pwd);
		return (NULL);
	}
	else
	{
		ft_strcpy(pwd, tmp);
		free(tmp);
	}
	if (pwd[ft_strlen(pwd) - 1] != '/')
		ft_strcat(pwd, "/");
	ret = path_clean(ft_strjoin(pwd, av));
	free(pwd);
	return (ret);
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
		fdir = cd_construct_path(env, av);
	return (fdir);
}

int			bi_cd(char **av, t_env_item *env)
{
	char	*finaldir;
	char	*pwd;
	char	*t;

	t = NULL;
	pwd = mgetenv(env, "PWD");
	if ((finaldir = cd_get_path(env, av[1])))
	{
		msetenv(&env, NULL, (t = ft_strjoin("OLDPWD=", pwd)), 1);
		if (chdir(finaldir))
			return (-1);
		free(t);
		msetenv(&env, NULL, (t = ft_strjoin("PWD=", finaldir)), 1);
		free(t);
		free(finaldir);
	}
	free(pwd);
	return (0);
}
