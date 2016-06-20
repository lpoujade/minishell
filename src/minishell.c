/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:51 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/20 18:39:52 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	sig_handlers_set(void)
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

int					exec_line(char *line)
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
				if ((ret = command(cmds[c])) && !cmds[c + 1])
					ft_putnbr(ret);
			free(cmds[c]);
			free(tmp);
			c++;
		}
		free(cmds);
	}
	return (1);
}

int					main(int ac, char **av)
{
	char	*line;
	int		fd;

	fd = 0;
	if (ac == 3 && !ft_strcmp(*(av + 1), "-c"))
		if ((fd = open(*(av + 2), O_RDONLY)) < 0)
			perror("minishell: open conf file");
	sig_handlers_set();
	parse_env_conf((*(av + 1) && *(av + 2) && **(av + 1) == '-'
				&& **((av + 1) + 1) == 'c') ? *(av + 2) : NULL);
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
			close (fd);
			fd = 0;
		}
		if (line && *line)
			free(line);
	}
	return (0);
}
