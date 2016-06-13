/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 12:41:33 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/13 13:15:25 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sighandler(int nb)
{
	if (nb == SIGINT)
		ft_putendl("\nKeyboard interrupt");
	else if (nb == SIGSEGV)
		ft_putendl("\nSegmentation fault");
	else
	{
		ft_putstr("SIGNAL ");
		ft_putnbr(nb);
		ft_putchar('\n');
	}
	sp_prompt();
	return ;
}
