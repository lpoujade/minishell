/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myexit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 19:43:35 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/03 20:23:23 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	myexit(t_env_item ***env, int envcount, int errnum, char *msg)
{
	int n;

	n = 0;
	if (msg)
		ft_putendl(msg);
	n = envfree(*env, envcount);
	exit(n ? n : errnum);
}
