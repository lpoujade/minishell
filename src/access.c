/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 12:12:22 by lpoujade          #+#    #+#             */
/*   Updated: 2016/07/28 18:06:49 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basicshell.h"

/*
** Search for str c1 in strs table c2
**
** Iter on c2 strs to find c1. Stop on first occurence of c1 in c2, or when
** NULL-terminating pointer has been reached in c2.
**
** @params c1: Searched string
** @params c2: Table of strings which may contains c1
**
** @return Pointer to c1 in c2, or NULL (reached end of c2 before finding c1)
*/

char				*cin_c2c(char *c1, char **c2)
{
	int	c;

	c = 0;
	while (*(c2 + c) && ft_strncmp(c1, *(c2 + c), ft_strlen(c1)))
		c++;
	return (*(c2 + c));
}

/*
** Concat next chars groups in path before ':' char with cmd
**
** Can be call with same value until no more folder to try in <path> or
** <cmd> was found in one on the folders
**
** @params path: Path variable ("/usr/bin:/personnal/binaries:/no")
** @params cmd: command name to find in the path (actually, name of binary file
**				contained in one of the path's folders
**
** @return Pointer to str representing <path_member>/<cmd>, or NULL
*/

static inline char	*cjoin(char *path, char *cmd)
{
	char	*ret;
	int		c;
	int		i;

	c = 0;
	errno = 0;
	if (!(ret = malloc(ft_strlen(cmd) + 1 +
					(ft_strlen(path) - ft_strlen(ft_strchr(path, ':'))))))
		exit(EXIT_FAILURE);
	while (path[c] && path[c] != ':')
	{
		ret[c] = path[c];
		c++;
	}
	ret[c] = '/';
	c++;
	i = 0;
	while (cmd[i])
	{
		ret[c + i] = cmd[i];
		i++;
	}
	ret[c + i] = 0;
	return (ret);
}

/*
** Try to find cmd in path
**
** Longer desc
** ...
**
** @params cmd: command (binary) to search trought path
** @params path: ':'-separated list of folders name
**
** @return Real path to cmd binary (ready to be passed to execve(), or NULL
*/

char				*in_path(char *cmd, char *path)
{
	char	*tpath;
	char	*ccm;
	int		c;

	tpath = path;
	c = 0;
	while (tpath && access((ccm = cjoin(tpath, cmd)), X_OK))
	{
		if ((tpath = ft_strchr(tpath, ':')))
		{
			tpath += 1;
			free(ccm);
		}
		c++;
	}
	if (!tpath)
	{
		free(ccm);
		ccm = NULL;
	}
	return (ccm);
}
