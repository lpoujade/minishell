/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrmstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/20 13:55:56 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/22 17:54:08 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrmstr(char *str, char *torm)
{
	char	*subs;
	int		c;
	int		sec;
	int		len;
	ft_putstr("in : "); ft_putendl(str);
	ft_putstr("tod: "); ft_putendl(torm);

	c = 0;
	sec = 0;
	len = ft_strlen(str);
	if (!(subs = ft_strstr(str, torm)))
		return (str);
	while (str[c] && c < len)
	{
		if ((str + c) == subs)
			sec += ft_strlen(torm);
		str[c] = (c + sec) <= len ? str[c + sec] : 0;
		c++;
	}
	str[c] = 0;
	ft_putstr("out: "); ft_putendl(str);
	return (str);
}
