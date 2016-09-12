/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myexit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 19:43:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/12 17:47:28 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	myexit(t_env_item **env, char *nu, char *msg)
{
	int errnum;
	int n;

	errnum = ft_atoi(nu);
	n = 0;
	if (msg)
		ft_putendl(msg);
	env_free(env);
	exit(n ? n : errnum);
}
