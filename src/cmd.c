/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 17:04:24 by lpoujade          #+#    #+#             */
/*   Updated: 2016/07/28 19:28:33 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basicshell.h"

int		forkexec(char *cmd, char **av, char **env)
{
	pid_t	father;
	int		ret_value;

	ret_value = 0;
	if ((father = fork()) < 0)
		exit(EXIT_FAILURE);
	if (!father)
		if ((execve(cmd, av, env)))
			exit(EXIT_FAILURE);
	if (father > 0)
		waitpid(father, &ret_value, 0);
	if (ret_value)
	{
		ft_putnbr(ret_value);
		ft_putchar(' ');
	}
	return (ret_value);
}

int		exec_cmd(t_shcmd *cmd)
{
	char		*f;
	char		*path;
	extern char **environ;

	f = NULL;
	if (!builtins(cmd))
	{
		if (!(path = getenv("PATH")))
			ft_putendl("NO PATH");
		else if ((f = in_path(cmd->cmd, path)))
			forkexec(f, cmd->args, environ);
		else
		{
			ft_putstr("bsh: command not found: ");
			ft_putendl(cmd->cmd);
		}
		if (f)
			free(f);
	}
	return (0);
}
