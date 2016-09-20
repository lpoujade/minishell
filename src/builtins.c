/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 19:28:46 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/20 11:49:59 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtins(t_shcmd *cmd, t_env_item **env)
{
	char	*tmp;

	tmp = NULL;
	if (!ft_strcmp(cmd->cmd, "cd"))
		bi_cd(cmd->args, *env);
	else if (!ft_strcmp(cmd->cmd, "env"))
		menv(env, cmd->args + 1);
	else if (!ft_strcmp(cmd->cmd, "unsetenv"))
		munsetenv(env, cmd->args[1]);
	else if (!ft_strcmp(cmd->cmd, "setenv"))
		msetenv(env, NULL, cmd->args[1], 1);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		myexit(env, cmd->args[1] ? cmd->args[1] : "0", NULL);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_putendl((tmp = mgetenv(*env, "PWD")));
	else if (!ft_strcmp(cmd->cmd, "echo"))
		bi_echo(cmd->args + 1);
	else
		return (0);
	if (tmp)
		free(tmp);
	return (1);
}

void		bi_echo(char **args)
{
	int		c;

	c = 0;
	while (args[c])
	{
		ft_putstr(args[c]);
		ft_putchar(' ');
		c++;
	}
	ft_putchar('\n');
}
