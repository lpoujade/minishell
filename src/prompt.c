/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 11:40:05 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/19 16:56:44 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*mygethostname(void)
{
	char	*hostname;

	if (!(hostname = malloc(HOSTNAME_MAX)))
		return (NULL);
	if (gethostname(hostname, HOSTNAME_MAX))
	{
		ft_putendl_fd(NULL, 1);
	}
	return (NULL);
}

void	sp_prompt(char *ps1)
{
	char	*ps = NULL; (void)ps1;
	char	*prompt = NULL;
	char	*tmp = NULL;

	/*
	if (!(prompt = malloc(PS1_MAX)))
		return (MALLOC_ERROR);
		*/

	if (!(prompt = getenv("PS1")))
		if (!(ps = ft_strdup(" %u @ - > ")))
			return ;

	if (ps)
		while (*ps)
		{
			if (*ps == '%')
			{
				if (*(ps + 1) == '~')
					ft_putstr(tmp = getcwd(NULL, 0));
				else if (*(ps + 1) == 'u')
					ft_putstr(getenv("LOGNAME") ?: getenv("USER"));
				else if (*(ps + 1) == 'h')
					ft_putstr(tmp = mygethostname());
				else
					ft_putchar(*ps);
				ps++;
			}
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
			ps++;
		}
	/*
	prompt = getcwd(NULL, 0);
	ft_putstr(prompt);
	ft_putstr(" > ");
	free(prompt);
	*/
	return ;
}
