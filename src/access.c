/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 12:12:22 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/24 13:47:26 by lpoujade         ###   ########.fr       */
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

char	*in_path(char *cmd, char *path)
{
	char	**dis_path;
	int		c;

	c = 0;
	dis_path = ft_strsplit(path, ':');
	while (dis_path[c] && access(ft_strjoin(dis_path[c], ft_strjoin("/", cmd)), X_OK))
		c++;
	if (dis_path[c])
		return (ft_strjoin(dis_path[c], ft_strjoin("/", cmd)));
	else
		return (NULL);
}
