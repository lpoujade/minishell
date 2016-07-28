/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shparse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 17:41:19 by lpoujade          #+#    #+#             */
/*   Updated: 2016/07/28 20:10:39 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basicshell.h"

static void	throw_quote_on(char *line)
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
		ft_putendl("bsh: missing terminating quote");
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

static void	dequote(char **av)
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

int			shparse(char *line, t_shcmd *cmd)
{
	char **splitted;
	char *q;

	splitted = NULL;
	if ((q = ft_strchr(line, '"')) && (*(q - 1) == ' ' || *(q - 1) == '\t'))
		throw_quote_on(line);
	cmd->args = ft_strsplit(line, " \t");
	cmd->cmd = cmd->args[0];
	dequote(cmd->args);
	return (cmd->args ? 1 : -1);
}
