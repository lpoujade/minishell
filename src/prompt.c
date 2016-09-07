/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 11:40:05 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/06 12:43:22 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** TODO security
*/

void	sp_prompt(t_env_item **env, int envcount)
{
	char	*prompt;
	char	*home;

	if ((prompt = getcwd(NULL, 0)))
	{
		if ((home = mgetenv(env, envcount, "HOME")) && ft_strstr(prompt, home)
				&& ft_strlen(home) > 2)
		{
			ft_putchar('~');
			ft_putstr(prompt + ft_strlen(home));
		}
		else
			ft_putstr(prompt);
		if (home)
			free(home);
		free(prompt);
	}
	ft_putstr(" > ");
	return ;
}
