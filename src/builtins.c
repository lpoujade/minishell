/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 12:24:23 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/23 05:19:42 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*tr_eq(char *s)
{
	int		c;
	char	*new;

	c = ft_strclchr(s, '=');
	new = ft_strnew(c);
	ft_strncat(new, s, c);
	return (new);
}

int					bi_suenv(char **av)
{
	int		ret;
	char	*var;

	var = NULL;
	ret = 0;
	if (!*av)
		return (-1);
	else if (**av == 's' && *(av + 1))
	{
		var = tr_eq(*(av + 1));
		ret = setenv(var, ft_strchr(*(av + 1), '='), 1);
	}
	else if (**av == 'u' && *(av + 1))
		ret = unsetenv(*(av + 1));
	else if (!*(av + 1))
		ft_putendl("USAGE");
	if (ret)
		ft_putendl("minishell: cannot modify env, or bad arguments");
	if (var)
		free(var);
	return (0);
}
