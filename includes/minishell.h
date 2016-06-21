/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:19:44 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/20 18:16:14 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stddef.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include "libft.h"

# define MALLOC_ERROR	-2
# define HOSTNAME_MAX	100
# define PS1_MAX		100

# define ft_putendl(x) ft_putendl_fd(x, 1)

extern char	**environ;

int		parse_env_conf(char *conffile);
int		bi_cd(char **av);
int		bi_env(char **av);
int		bi_suenv(char **av);
void	sp_prompt(char *ps1);
int		exec_line(char *line);
int		command(char *line);
char	*in_path(char *cmd, char *path);
char	*cin_c2c(char *c1, char **c2);
void	sighandler(int nb);
int		forkexec(char *cmd, char **av, char **env);
#endif
