/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:51 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/13 15:28:41 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline
void	sig_handlers_set(void)
{
	int	c;

	c = 0;
	while (++c <= 31)
		signal(c, &sighandler);
}

int		main(void)
{
	char	*line;
	char	**cmds;

	sig_handlers_set();
	line = NULL;
	while (1)
	{
		sp_prompt();
		if (get_next_line(0, &line) < 0)
			exit(EXIT_FAILURE);
		if (line && (cmds = ft_strsplit(line, ';')))
			while (*cmds)
			{
				command(*cmds);
				cmds++;
			}
		else
			exit (EXIT_SUCCESS);
		if (line && *line)
			free(line);
		line = NULL;
	}
	return (0);
}
