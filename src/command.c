/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 12:37:22 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/20 18:43:27 by lpoujade         ###   ########.fr       */
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
	short ret;

	ret = 0;
	if (!ft_strcmp(*av, "exit"))
		exit(*(av + 1) ? ft_atoi(*(av + 1)) : EXIT_SUCCESS);
	else if (!ft_strcmp(*av, "cd"))
		ret = bi_cd(av + 1);
	else if (!ft_strcmp(*av, "env"))
		ret = bi_env(av + 1);
	else if (!ft_strcmp(*av, "echo"))
	{
		while (*av++)
		{
			if (*av && **av == '$')
				ft_putstr(getenv(*av + 1));
			else
				ft_putstr(*av);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	else if (!ft_strcmp(*av, "setenv") || !ft_strcmp(*av, "unsetenv"))
		bi_suenv(av);
	else
		return (404);
	return (ret);
}

int			command(char *line)
{
	char	**av;
	char	*path;
	char	*cmd;
	int		ret;
	short	c;

	ret = 0;
	c = 0;
	cmd = NULL;
	path = getenv("PATH");
	av = ft_strsplit(line, "\t  ");
	if ((ret = in_builtins(av)) != 404)
		;
	else if (!(access(*av, X_OK)) || (path && (cmd = in_path(*av, path))))
		ret = forkexec(cmd ? cmd : *av, av, (char**)environ);
	else
		ft_putendl((cmd = ft_strjoin("minishell: command not found: ", *av)));
	while (av[c])
	{
		free(*(av + c));
		c++;
	}
	free(av);
	ft_memdel((void**)&cmd);
	return (ret);
}
