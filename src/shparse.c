/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shparse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 17:41:19 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/12 17:33:12 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		throw_quote_on(char *line)
{
	int c;
	int	qount;

	c = 0;
	qount = 0;
	while (line[c])
	{
		if (line[c] == '"')
			qount ? qount++ : qount--;
		if (line[c] == ' ' && qount)
			line[c] = '"';
		c++;
	}
	if (qount)
		ft_putendl("minishell: missing terminating quote");
}

static void		throw_quote_off(char *line)
{
	int c;
	int	qount;

	c = 0;
	qount = 0;
	while (line[c])
	{
		if (line[c] == '"')
			qount ? qount++ : qount--;
		if (line[c] == '"' && (line[c + 1] && line[c - 1]))
			line[c] = ' ';
		c++;
	}
}

static void		dequote(char **av)
{
	char **str;
	char *tmp;

	str = av + 1;
	while (*str)
	{
		if (ft_strchr(*str, '"'))
		{
			tmp = *str;
			throw_quote_off(*str);
			*str = ft_strtrim(*str, "\" ");
			free(tmp);
		}
		str++;
	}
}

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
	char	*q;
	int		c;

	c = 0;
	splitted = NULL;
	if ((q = ft_strchr(line, '"')) && (*(q - 1) == ' ' || *(q - 1) == '\t'))
		throw_quote_on(line);
	cmd->args = ft_strsplit(line, " \t");
	cmd->cmd = cmd->args[0];
	dequote(cmd->args);
	while (cmd->args[c])
	{
		if (*(cmd->args[c]) == '$')
			envvars_replace(&(cmd->args[c]), env);
		c++;
	}
	return (cmd->args ? 1 : -1);
}
