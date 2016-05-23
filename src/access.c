/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 12:12:22 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/23 12:25:53 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cin_c2c(char *c1, char const **c2)
{
	int	c;

	c = 0;
	while (*(c2 + c) && ft_strncmp(c1, *(c2 + c), ft_strlen(c1)))
		c++;
	return (*(c2 + c));
}

int		in_path(char *cmd, char *path)
{
	char	**dis_path;
	int		c;

	c = 0;
	dis_path = ft_strsplit(path, ':');
	while (access(ft_strjoin(*(dis_path + c), cmd), X_OK))
		c++;
	if (*(dis_path + c))
		return (1);
	else
		return (0);
}
