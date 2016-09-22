/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrmstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 13:55:56 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/22 12:24:54 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrmstr(char *str, char *torm)
{
	char	*subs;
	int		c;
	int		sec;

	c = 0;
	sec = 0;
	if (!(subs = ft_strstr(str, torm)))
		return (str);
	while (str[c])
	{
		if ((str + c) == subs)
			sec += ft_strlen(torm);
		str[c] = str[c + sec];
		c++;
	}
	str[c] = 0;
	return (str);
}
