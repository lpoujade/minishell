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

void	bi_cd(char **av)
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
		ft_putendl("NO PATH");
}
