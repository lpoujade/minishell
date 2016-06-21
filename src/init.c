/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 20:28:49 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/17 18:49:28 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_env_conf(char *conffile)
{
	char		**nenv;
	int			c;
	int			i;

	c = 0;
	i = 0;
	nenv = NULL;
	while (environ[c])
		c++;
	if (!(nenv = malloc(sizeof(char**) * c)))
		exit(EXIT_FAILURE);
	while (i < c)
	{
		nenv[i] = ft_strdup(environ[i]);
		i++;
	}
	nenv[i] = NULL;
	environ = nenv;
	if (conffile)
	{}
	return (0);
}
