/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:49:24 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/22 15:00:41 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char *set)
{
	char	*ret;
	int		len;
	int		cd;
	int		cf;

	cd = 0;
	cf = 0;
	len = (ft_strlen(s) - 1);
	while (ft_strchr(set, s[cd]))
		cd++;
	while (ft_strchr(set, s[len]))
	{
		len--;
		cf++;
	}
	if ((cf + cd) != 0 && cf != (int)ft_strlen(s))
	{
		if ((ret = ft_strnew(ft_strlen(s) - (cd + cf))))
			ft_strncpy(ret, (s + cd), (ft_strlen(s) - (cd + cf)));
	}
	else if (cf == (int)ft_strlen(s))
		return ("");
	else
		ret = ft_strdup(s);
	return (ret);
}
