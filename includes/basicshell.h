/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 17:37:43 by lpoujade          #+#    #+#             */
/*   Updated: 2016/07/28 20:10:39 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICSHELL_H
# define BASICSHELL_H

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

typedef struct	s_shcmd
{
	char		*cmd;
	char		**args;
}				t_shcmd;

void			ft_strtdel(char **str_t);
int				shparse(char *line, t_shcmd *cmd);
void			shell_loop(void);
int				forkexec(char *cmd, char **av, char **env);
char			*in_path(char *cmd, char *path);
char			*cin_c2c(char *c1, char **c2);
int				exec_cmd(t_shcmd *cmd);
int				builtins(t_shcmd *cmd);
void			sp_prompt(void);

#endif
