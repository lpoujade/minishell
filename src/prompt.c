/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 11:40:05 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/22 14:13:33 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** TODO security
*/

void	sp_prompt(t_env_item *env, int ret)
{
	char	*prompt;
	char	*home;

	if (ret != 0)
		ft_putnbr(ret);
	if ((prompt = mgetenv(env, "PWD")))
	{
		if ((home = mgetenv(env, "HOME")) && ft_strstr(prompt, home))
		{
			ft_putchar('~');
			ft_putstr(prompt + ft_strlen(home));
		}
		else
			ft_putstr(prompt);
		ft_memdel((void**)&home);
		free(prompt);
	}
	ft_putstr(" > ");
}
