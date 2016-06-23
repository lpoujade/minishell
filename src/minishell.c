/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:51 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/23 18:26:24 by lpoujade         ###   ########.fr       */
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

int					main(int ac, char **av)
{
	int		fd;

	fd = 0;
	if (ac == 3 && !ft_strcmp(*(av + 1), "-c"))
		if ((fd = open(*(av + 2), O_RDONLY)) < 0)
			ft_putendl_fd("minishell: open conf file failed", 2);
	sig_handlers_set();
	parse_env_conf((*(av + 1) && *(av + 2) && **(av + 1) == '-'
				&& **((av + 1) + 1) == 'c') ? *(av + 2) : NULL);
	shell_loop(fd);
	return (0);
}
