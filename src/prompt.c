/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 11:40:05 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/12 12:23:35 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sp_prompt(void)
{
	char	*prompt;

	prompt = NULL;
	prompt = getcwd(prompt, 0);
	ft_putstr(prompt); ft_putstr(" > ");
	free (prompt);
	return ;
}
