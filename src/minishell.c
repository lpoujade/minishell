/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:51 by lpoujade          #+#    #+#             */
/*   Updated: 2016/05/24 13:47:25 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char const **environ;

int		main(int ac, char **av)
{
	(void)ac;
	pid_t	father;
	int		c;
	char	*line;

	father = 0;
	line = NULL;
	while (1)
	{
		ft_putstr("$> ");
		c = 0;
		if (get_next_line(0, &line) < 0)
			exit (127);
		if (!ft_strcmp(line, "exit"))
			return (EXIT_SUCCESS);
		else if (!ft_strcmp(line, "env"))
			while (*(environ + c))
			{
				ft_putendl(*(environ + c));
				c++;
			}
		else if (line && *line)
		{
			if ((line = in_path(line, cin_c2c("PATH", (char**)environ))))
			{
				if (!father)
					father = fork();
				if (!father)
					execve(line, av, NULL);
				else if (father > 0)
					wait(NULL);
			}
			else
				ft_putendl("command not found");
		}
		else
			if (!line && !*line)
				return (EXIT_SUCCESS);
	}
}
