/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:49:24 by lpoujade          #+#    #+#             */
/*   Updated: 2016/07/28 00:04:08 by liumsade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 ** @name    Trim a string
 ** @brief   Remove trailings and leadings set of characters
 ** @ingroup libft
 **
 ** ft_strtrim(char *str, char *char_set) returns a string without each 
 ** character in the char_set string if between the beginning or the end
 ** and the first other character (which don't appear in char_set)
 **
 ** @param [in] char *str        String to trim
 ** @param [in] char *char_set   Characters to use for trim
 **
 ** @retval char *  Pointer to new string trimmed
 **
 ** Example Usage:
 ** @code
 **    ft_strtrim("' fyah '", "' ")
 ** @endcode
 ** Will return fyah
*/

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
