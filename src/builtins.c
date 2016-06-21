/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 12:24:23 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/20 19:26:55 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** env launch a process with enventually modified actual env
** if no process, env is displayed
** env [-u NAME] [NAME=value] [cmd]
** -u delete NAME
** -i clear env
*/

int					bi_env(char **av)
{
	int	c;

	c = 0;
	if (!*av)
		while (*(environ + c))
		{
			ft_putendl(*(environ + c));
			c++;
		}
	else if (**av == '-' && **(av + 1) == 'u')
	{}
	else if (**av == '-' && *(*av + 1) == 'i' && *(av + 1))
		forkexec(*(av + 1), (av + 1), NULL);
	else if (**av == '-' && **(av + 1) == 'i')
	{}
	return (0);
}

static inline char	*tr_eq(char *s)
{
	int		c;
	char	*new;

	c = ft_strclchr(s, '=');
	new = ft_strnew(c);
	ft_strncat(new, s, c);
	ft_putendl(new);
	return (new);
}

int					bi_suenv(char **av)
{
	char	*var;

	var = NULL;
	if (!*av)
		return (-1);
	else if (**av == 's' && *(av + 1))
	{
		if (setenv((var = tr_eq(*(av + 1))), ft_strchr(*(av + 1), '='), 1))
			ft_putendl("minishell: setenv error");
	}
	else if (**av == 'u')
	{
		if (*(av + 1) && unsetenv(*(av + 1)))
			ft_putendl("minishell: unsetenv error");
	}
	else
	{
		if (!*(av + 1))
			ft_putendl("USAGE");
		else if (setenv(*av, *(av + 1), 1))
			perror("minishell: env()");
	}
	if (var)
		free(var);
	return (0);
}
