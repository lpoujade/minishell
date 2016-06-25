/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 04:30:12 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/25 02:22:20 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(int fd)
{
	char	*line;
	short	gnl_ret;

	while (1)
	{
		line = NULL;
		if (fd == 0)
			sp_prompt();
		if ((gnl_ret = get_next_line(fd, &line)) < 0)
			exit(EXIT_FAILURE);
		if (!exec_line(line) && fd == 0)
			exit(EXIT_SUCCESS);
		else if (fd != 0 && gnl_ret == 0)
		{
			close(fd);
			fd = 0;
		}
		if (line && *line)
			free(line);
	}
}

int		exec_line(char *line)
{
	char	**cmds;
	char	*tmp;
	int		c;
	short	ret;

	c = 0;
	ret = 0;
	tmp = NULL;
	if (!line)
		return (0);
	if ((cmds = ft_strsplit(line, ";")))
	{
		while (cmds[c])
		{
			if (*(tmp = ft_strtrim(cmds[c])) != '#')
				if ((ret = command(cmds[c], environ, 1)) && !cmds[c + 1])
					;
					//ft_putnbr(ret);
			free(cmds[c]);
			free(tmp);
			c++;
		}
		free(cmds);
	}
	return (1);
}
