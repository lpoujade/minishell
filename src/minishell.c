/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:02:51 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/25 01:48:46 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
** Register certains signals to a sigHandler function
**
** Set one function callback to all signals except :
** SIGKILL, SIGSTOP, SIGSEGV, SIGBUS, SIGQUIT & SIGTERM
** TODO: documents wichs are not handled for debug and which are not by
** obligations
**
** @param Nothing.
** @return Nothing.
*/
static inline void	sig_handlers_set(void)
{
	int	c;

	c = 0;
	while (++c <= 31)
		if (c != SIGKILL && c != SIGSTOP && c != SIGSEGV && c != SIGBUS
				&& c != SIGQUIT && c != SIGTERM)
			if (signal(c, &sighandler) == SIG_ERR)
			{
				ft_putstr_fd("minishell: signal ", 2);
				ft_putnbr_fd(c, 2);
				perror(" not set");
			}
}

/**
** Short desc
**
** Longer desc
** ...
**
** @params ac
** @params av
**
** @return nothing
*/
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
