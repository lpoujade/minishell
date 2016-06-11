/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:51 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/11 17:55:53 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char const **environ;

static inline void	forkexec(char *cmd, char **av)
{
	pid_t	father;

	if ((father = fork()) < 0)
		exit (EXIT_FAILURE);
	if (!father)
		execve(cmd, av, (char*const*)environ);
	if (father > 0)
		waitpid(father, NULL, 0);
}

int		main(void)
{
	int		c;
	char	*line;

	line = NULL;
	while (1)
	{
		c = 0;
		ft_putstr("$> ");
		if (get_next_line(0, &line) < 0)
			exit (EXIT_FAILURE);
		command(line);
		if (line && *line)
			free(line);
		line = NULL;
	}
	return (0);
}

int		command(char *line)
{
	char	**av;
	int		c;

	c = 0;
	if (line && *line)
	{
		av = ft_strsplit(line, ' ');
		if (!ft_strcmp(*av, "exit"))
			exit (EXIT_SUCCESS);
		else if (!ft_strcmp(*av, "env"))
			while (*(environ + c))
			{
				ft_putendl(*(environ + c));
				c++;
			}
		if (access(*av, X_OK) > 0)
			ft_putendl("EXECUTABLE");
		else if ((*av = in_path(*av, cin_c2c("PATH", (char**)environ) + 5)))
			forkexec(*av, av);
		else
			ft_putendl("command not found");
	}
	else
		if (!line)
			exit (EXIT_SUCCESS);
	return (0);
}
