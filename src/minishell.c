/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:51 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/12 14:38:47 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char const **environ;

static inline void	forkexec(char *cmd, char **av)
{
	pid_t	father;
	int		ret_value;

	ret_value = 0;
	if ((father = fork()) < 0)
		exit(EXIT_FAILURE);
	if (!father)
		if ((execve(cmd, av, (char*const*)environ)))
			exit(EXIT_FAILURE);
	if (father > 0)
		waitpid(father, &ret_value, 0);
	if (ret_value)
	{
		ft_putnbr(ret_value);
		ft_putchar(' ');
	}
}

int		main(void)
{
	int		c;
	char	*line;

	line = NULL;
	while (1)
	{
		c = 0;
		sp_prompt();
		if (get_next_line(0, &line) < 0)
			exit(EXIT_FAILURE);
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
	char	*path;

	path = getenv("PATH");
	c = 0;
	if (line && *line)
	{
		av = ft_strsplit(line, ' ');
		if (!ft_strcmp(*av, "exit"))
			exit(EXIT_SUCCESS);
		else if (!ft_strcmp(*av, "cd"))
			bi_cd(av + 1);
		else if (!ft_strcmp(*av, "env"))
			env(av + 1);
		else if (!(access(*av, X_OK)))
			forkexec(*av, av);
		else if ((*av = in_path(*av, path)))
			forkexec(*av, av);
		else
			ft_putendl("command not found");
	}
	else
		if (!line)
			exit(EXIT_SUCCESS);
	return (0);
}
