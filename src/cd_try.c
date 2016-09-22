/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_try.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:02:54 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/22 18:03:07 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			try_dir(char *dir, char *arg)
{
	int	ret;

	if (access(dir, X_OK))
	{
		if (access(dir, F_OK))
		{
			ft_putstr_fd("minishell: no folder: ", 2);
			ft_putendl_fd(arg, 2);
		}
		else
		{
			ft_putstr_fd("minishell: no rights for folder: ", 2);
			ft_putendl_fd(arg, 2);
		}
		return (2);
	}
	else if ((ret = chdir(dir)))
	{
		ft_putstr_fd("minishell: unknow error for folder: ", 2);
		ft_putendl_fd(arg, 2);
		return (ret);
	}
	return (0);
}
