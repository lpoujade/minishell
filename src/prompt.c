/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 11:40:05 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/17 17:59:22 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sp_prompt(void)
{
	char	*prompt;

	prompt = NULL;
	prompt = getenv("LOGNAME");
	if (!prompt)
		prompt = getenv("USER");
	if (prompt)
	{
		ft_putstr(prompt);
		ft_putchar(' ');
	}
	prompt = getcwd(NULL, 0);
	ft_putstr(prompt);
	ft_putstr(" > ");
	free(prompt);
	return ;
}
