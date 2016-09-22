/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 20:30:22 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/13 20:31:41 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strtnew(size_t size)
{
	char	**k;

	if (!(k = malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	while (size)
		k[size--] = NULL;
	return (k);
}
