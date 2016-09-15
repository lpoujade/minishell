/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 17:30:27 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/15 16:45:51 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **environ)
{
	t_env_item	*env;

	(void)ac;
	(void)av;
	env = NULL;
	if (*environ)
	{
		if (env_populate(&env, environ) < 0)
		{
			ft_putendl_fd("minishell: error reading environ", 2);
			return (-1);
		}
	}
	else
		env = env_new_item(NULL, "SHELL=minishell", 0);
	shell_loop(&env);
	env_free(&env);
	return (EXIT_SUCCESS);
}

void	shell_loop(t_env_item **env)
{
	char	*line;
	t_shcmd	cmd;
	int		ret;

	while (1)
	{
		sp_prompt(*env);
		if ((ret = get_next_line(1, &line)) < 0)
			myexit(env, "-1", "Error on input");
		else if (!ret)
			return ;
		else
		{
			if (*line)
			{
				if (shparse(line, &cmd, *env) > 0)
					exec_cmd(&cmd, *env);
				else
					ft_putendl_fd("minishell: parse error", 2);
			}
			free(line);
			line = NULL;
		}
	}
	env_free(env);
}
