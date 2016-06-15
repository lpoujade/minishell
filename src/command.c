/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 12:37:22 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/15 19:51:46 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			forkexec(char *cmd, char **av, char **env)
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

static int	in_builtins(char **av)
{
	if (!ft_strcmp(*av, "exit"))
		exit(EXIT_SUCCESS);
	else if (!ft_strcmp(*av, "cd"))
		bi_cd(av + 1);
	else if (!ft_strcmp(*av, "env"))
		bi_env(av + 1);
	else
		return (0);
	return (1);
}

int			command(char *line)
{
	char	**av;
	char	*path;
	char	*cmd;
	int		ret;

	ret = 0;
	cmd = NULL;
	path = getenv("PATH");
	av = ft_strsplit(line, "\t ");
	if (!in_builtins(av))
	{
		if (!(access(*av, X_OK)) || (path && (cmd = in_path(*av, path))))
			ret = forkexec(cmd ? cmd : *av, av, (char**)environ);
		else
			ft_putendl((cmd = ft_strjoin(*av, ": command not found")));
	}
	while (*av)
	{
		free(*av);
		*av = NULL;
		av++;
	}
	if (cmd)
		free(cmd);
	return (ret);
}
