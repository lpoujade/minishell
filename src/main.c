/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 13:51:37 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/22 14:56:25 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		shell_init(t_env_item **env)
{
	char	*pwd;
	char	*t;

	if (!*env)
		msetenv(env, NULL, "PATH=/usr/bin:/bin:/usr/sbin:/sbin", 1);
	if (!(pwd = malloc(sizeof(char) * PATH_MAX)))
		return (-1);
	if (!(pwd = getcwd(pwd, PATH_MAX)))
	{
		ft_putendl_fd("minishell: start in bad directory", 2);
		exit(10);
	}
	msetenv(env, NULL, (t = ft_strjoin("PWD=", pwd)), 1);
	free(t);
	free(pwd);
	return (0);
}

int				main(int ac, char **av, char **environ)
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
		env = NULL;
	shell_init(&env);
	shell_loop(&env);
	env_free(&env);
	return (EXIT_SUCCESS);
}

void			shell_loop(t_env_item **env)
{
	char	*line;
	t_shcmd	cmd;
	int		gnl_ret;
	int		ret;

	ret = 0;
	while (1)
	{
		sp_prompt(*env, ret);
		if ((gnl_ret = get_next_line(1, &line)) < 0)
			myexit(env, "-1", "Error on input");
		else if (!gnl_ret)
			break ;
		else
		{
			if (*line)
			{
				if (shparse(line, &cmd, *env) > 0)
					ret = exec_cmd(&cmd, env);
				else
					ft_putendl_fd("minishell: parse error", 2);
			}
			ft_strdel(&line);
		}
	}
}
