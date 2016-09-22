/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:35:31 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/22 18:49:36 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		setenv_check(char *pair)
{
	char	*t;

	if (!(t = ft_strchr(pair, '=')))
	{
		ft_putendl_fd("minishell: bad parameter", 2);
		return (1);
	}
	if (!*(t + 1))
	{
		ft_putendl_fd("minishell: bad parameter", 2);
		return (1);
	}
	return (0);
}
