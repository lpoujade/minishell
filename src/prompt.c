/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 11:40:05 by lpoujade          #+#    #+#             */
/*   Updated: 2016/07/28 20:15:14 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basicshell.h"

/*
 ** TODO security
*/

void	sp_prompt(void)
{
	char	*prompt;
	char	*home;

	prompt = getcwd(NULL, 0);
	if ((home = getenv("HOME")) && ft_strstr(prompt, home))
	{
		ft_putchar('~');
		ft_putstr(prompt + ft_strlen(home));
	}
	else
		ft_putstr(prompt);
	ft_putstr(" > ");
	free(prompt);
	return ;
}
