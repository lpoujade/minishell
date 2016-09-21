/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 11:40:05 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/21 16:16:43 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** TODO security
*/

void	sp_prompt(t_env_item *env)
{
	char	*prompt;
	char	*home;
	char	*prec_ret_val;

	if ((prec_ret_val = mgetenv(env, "?")) && ft_atoi(prec_ret_val) != 0)
		ft_putstr(prec_ret_val);
	ft_memdel((void**)&prec_ret_val);
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
