/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 12:41:33 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/13 15:59:59 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sighandler(int nb)
{
	if (nb == SIGINT)
	{
		ft_putendl("\nKeyboard interrupt");
		sp_prompt();
	}
	else if (nb == SIGSEGV)
	{
		ft_putendl("\nSomething bad happen ! but that's ok now");
		exit (11);
	}
	else if (nb == SIGCHLD || nb == SIGWINCH)
		;
	else
	{
		ft_putstr("SIGNAL ");
		ft_putnbr(nb);
		ft_putchar('\n');
	}
	return ;
}
