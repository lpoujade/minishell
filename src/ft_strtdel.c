/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 18:19:45 by lpoujade          #+#    #+#             */
/*   Updated: 2016/07/27 18:51:26 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basicshell.h"

void	ft_strtdel(char **str_t)
{
	while (*str_t)
	{
		free(*str_t);
		*str_t = NULL;
		str_t++;
	}
}
