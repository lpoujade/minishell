/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 04:30:12 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/23 04:31:13 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(int fd)
{
	char	*line;

	while (1)
	{
		line = NULL;
		if (fd == 0)
			sp_prompt();
		if (get_next_line(fd, &line) < 0)
			exit(EXIT_FAILURE);
		if (!exec_line(line) && fd == 0)
			exit(EXIT_SUCCESS);
		else if (fd != 0)
		{
			close(fd);
			fd = 0;
		}
		if (line && *line)
			free(line);
	}
}
