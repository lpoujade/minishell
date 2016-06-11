/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:51 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/11 11:50:13 by lpoujade         ###   ########.fr       */
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
	if (!*environ)
		return (EXIT_FAILURE);
	while (1)
	{
		ft_putstr("$> ");
		c = 0;
		if (get_next_line(0, &line) < 0)
			exit (127);
		if (!ft_strcmp(line, "exit"))
			return (EXIT_SUCCESS);
		else if (!ft_strcmp(line, "whereami"))
			ft_putendl(ft_itoa(father));
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
					execv(line, av);
				if (father > 0)
					waitpid(father, NULL, 0);
			}
			else
				ft_putendl("command not found");
			father = 0;
		}
		else
			if (!line && !*line)
				return (EXIT_SUCCESS);
		if (line)
			free (line);
	}
	return (0);
}
