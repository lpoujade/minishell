/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 12:12:22 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/15 15:55:10 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cin_c2c(char *c1, char **c2)
{
	int	c;

	c = 0;
	while (*(c2 + c) && ft_strncmp(c1, *(c2 + c), ft_strlen(c1)))
		c++;
	return (*(c2 + c));
}

static inline
char	*cjoin(char *path, char *cmd)
{
	char	*ret;
	int		c;
	int		i;

	c = 0;
	i = 0;
	ret = malloc(ft_strlen(cmd) + ft_strlen(cmd) - ft_strlen(ft_strchr(cmd, ':')));
	while (path[c] && path[c] != ':')
	{
		ret[c] = path[c];
		c++;
	}
	ret[c] = '/';
	c++;
	while (cmd[i])
	{
		ret[c + i] = cmd[i];
		i++;
	}
	ret[c + i] = 0;
	return (ret);
}

char	*in_path(char *cmd, char *path)
{
	char	*tpath;
	char	*ccm;
	int		c;

	tpath = path;
	ccm = ft_strdup(cmd);
	free(cmd);
	c = 0;
	while (tpath && access((cmd = cjoin(tpath, ccm)), X_OK))
	{
		if ((tpath = ft_strchr(tpath, ':')))
			tpath += 1;
		c++;
		free(cmd);
	}
	if (!tpath)
		cmd = NULL;
	free(ccm);
	return (cmd);
}
