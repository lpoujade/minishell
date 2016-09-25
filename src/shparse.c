/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shparse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 17:41:19 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/20 10:56:37 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		envvars_replace(char **str, t_env_item *env)
{
	char	*value;

	if ((value = mgetenv(env, (*str) + 1)))
	{
		free(*str);
		*str = value;
	}
	else
	{
		free(*str);
		*str = ft_strdup("");
	}
}

int				shparse(char *line, t_shcmd *cmd, t_env_item *env)
{
	char	**splitted;
	int		c;

	c = 0;
	splitted = NULL;
	if (!(*(cmd->args = ft_strsplit(line, " \t"))))
		return (-1);
	cmd->cmd = cmd->args[0];
	while (cmd->args[c])
	{
		if (*(cmd->args[c]) == '$')
			envvars_replace(&(cmd->args[c]), env);
		c++;
	}
	return (cmd->args ? 1 : -1);
}
