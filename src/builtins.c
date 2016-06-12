/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 12:24:23 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/12 15:13:25 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char const **environ;

int		bi_cd(char **av)
{
	int	c;
	char	*oldpwd;
	char	*npath;

	c = 0;
	oldpwd = getenv("OLDPWD");
	npath = getcwd(NULL, 0);
	setenv("OLDPWD", npath, 1);
	free(npath);
	npath = NULL;
	if (!*av)
		   npath = getenv("HOME");
	else if (**av == '-')
	{
		npath = oldpwd;
		ft_putendl(oldpwd);
	}
	else if (*av)
	{
		if ((!(access(*av, X_OK))))
			npath = *av;
		else
			ft_putendl("directory not accessible");
	}
	if (npath && *npath)
		chdir(npath);
	else
		return (-1);
	return (0);
}

int		env(char **av)
{
	int	c;

	c = 0;
	errno = 0;
	if (!*av)
		while (*(environ + c))
		{
			ft_putendl(*(environ + c));
			c++;
		}
	else if (*((*av) + 1) == 'i')
		; // forkexec ( cmd ; env = NULL )
	else if (*((*av) + 1) == 'u')
	{
		if (!*(av + 1))
			ft_putendl("which one ?");
		else if (unsetenv(*(av + 1)))
			perror("minishell: env()");
	}
	else
	{
		if (!*(av + 1))
			ft_putendl("USAGE");
		else if (setenv(*av, *(av + 1), 1))
			perror("minishell: env()");
	}
	return (0);
}
