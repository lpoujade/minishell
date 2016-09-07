/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 17:30:27 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/06 13:16:40 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **environ)
{
	t_env_item	**env;
	int			envcount;

	(void)ac;
	(void)av;
	envcount = 0;
	env = NULL;
	if (environ)
	{
		if ((envcount = env_populate(&env, environ)) < 0)
		{
			ft_putendl_fd("minishell: error reading environ", 2);
			return (-1);
		}
	}
	else
	{
		*env = malloc(sizeof(t_env_item));
		env = NULL;
	}
	shell_loop(env, envcount);
	envfree(env, envcount);
	return (EXIT_SUCCESS);
}

void	shell_loop(t_env_item **env, int envcount)
{
	char	*line;
	t_shcmd	cmd;
	int		ret;

	while (1)
	{
		sp_prompt(env, envcount);
		if ((ret = get_next_line(1, &line)) < 0)
			myexit(&env, envcount, -1, "Error on input");
		else if (!ret)
			return ;
		else
		{
			if (*line)
			{
				if (shparse(line, &cmd, env, envcount) > 0)
					exec_cmd(&cmd, env, envcount);
				ft_strtdel(cmd.args);
				free(cmd.args);
			}
			free(line);
			line = NULL;
		}
	}
}
