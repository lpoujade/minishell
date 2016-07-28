/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 17:30:27 by lpoujade          #+#    #+#             */
/*   Updated: 2016/07/28 20:10:39 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basicshell.h"

/*
** Basic loop on get_next_line:
** print little promtp; wait for input
** quit if nothing; else parse the line
** free all; loop
*/

int		main(void)
{
	shell_loop();
	return (EXIT_SUCCESS);
}

void	shell_loop(void)
{
	char	*line;
	t_shcmd	cmd;
	int		ret;

	while (1)
	{
		sp_prompt();
		if ((ret = get_next_line(1, &line)) < 0)
			ft_putendl("ERROR ON INPUT");
		else if (!ret)
			return ;
		else
		{
			if (*line)
			{
				if (shparse(line, &cmd) > 0)
					exec_cmd(&cmd);
				ft_strtdel(cmd.args);
				free(cmd.args);
			}
			free(line);
			line = NULL;
		}
	}
}
