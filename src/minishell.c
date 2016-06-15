/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:51 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/15 15:41:09 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline
void	sig_handlers_set(void)
{
	int	c;

	c = 0;
	while (++c <= 31)
		if (c != SIGKILL && c != SIGSTOP && c != SIGSEGV && c != SIGBUS)
		if (signal(c, &sighandler) == SIG_ERR)
		{
			ft_putstr_fd("minishell: signal ", 2);
			ft_putnbr_fd(c, 2);
			perror(" not set");
		}
}

int		exec_line(char *line)
{
	char	**cmds;
	int		c;
	//char	**if_cmds;

	c = 0;
	if (!line)
		return (1);
	if ((cmds = ft_strsplit(line, ";")))
	{
		while (cmds[c])
		{
			command(cmds[c]);
			free(*(cmds + c));
			c++;
		}
		free (cmds);
	}
	return (0);
}
/*
			if (0 && (if_cmds = ft_strsplit(*cmds, "&")))
				while (*if_cmds)
				{
					if (!command(*if_cmds))
						break ;
					free(*if_cmds);
					if_cmds++;
				}
				*/

int		main(void)
{
	char	*line;

	sig_handlers_set();
	/*
	parse_env_conf((*(av + 1) && *(av + 2) && **(av + 1) == '-'
			&& **((av + 1) + 1) = 'c') ? *(av + 2) : NULL);
			*/
	line = NULL;
	while (1)
	{
		sp_prompt();
		if (get_next_line(0, &line) < 0)
			exit(EXIT_FAILURE);
		if (exec_line(line))
			exit (EXIT_SUCCESS);
		if (line && *line)
			free(line);
		line = NULL;
	}
	return (0);
}
