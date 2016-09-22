/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 main.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: lpoujade <lpoujade@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2016/07/27 17:30:27 by lpoujade		   #+#	  #+#			  */
/*	 Updated: 2016/09/22 12:37:43 by lpoujade		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

static int		shell_init(t_env_item **env)
{
	char	*pwd;
	char	*t;

	if (!*env)
		msetenv(env, NULL, "PATH=/usr/bin:/bin:/usr/sbin:/sbin", 1);
	if (!(pwd = malloc(PATH_MAX * sizeof(char))))
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
	int		ret;

	while (1)
	{
		sp_prompt(*env);
		if ((ret = get_next_line(1, &line)) < 0)
			myexit(env, "-1", "Error on input");
		else if (!ret)
			break ;
		else
		{
			if (*line)
			{
				if (shparse(line, &cmd, *env) > 0)
					exec_cmd(&cmd, env);
				else
					ft_putendl_fd("minishell: parse error", 2);
			}
			free(line);
			line = NULL;
		}
	}
}
