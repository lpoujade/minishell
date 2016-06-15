/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 12:37:22 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/15 15:51:40 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	forkexec(char *cmd, char **av, char **env)
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
}

int		command(char *line)
{
	char	**av;
	int		c;
	char	*path;
	char	*cmd;
	char	**oav;

	cmd = NULL;
	path = getenv("PATH");
	c = 0;
	if (line && *line)
	{
		av = ft_strsplit(line, "\t ");
		oav = av;
		if (!ft_strcmp(*av, "exit"))
			exit(EXIT_SUCCESS);
		else if (!ft_strcmp(*av, "cd"))
			bi_cd(av + 1);
		else if (!ft_strcmp(*av, "env"))
			bi_env(av + 1);
		else if (!(access(*av, X_OK)) || (path && (cmd = in_path(*av, path))))
		{
			forkexec(cmd ? cmd : *av, av, (char**)environ);
			free(cmd);
		}
		else
		{
			ft_putstr(*av);
			ft_putendl(": command not found");
		}
		while (*oav)
		{
			free (*oav);
			oav++;
		}
	}
	return (0);
}
