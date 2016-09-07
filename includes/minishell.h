/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 17:37:43 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/07 16:40:44 by lpoujade         ###   ########.fr       */
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

# include "shell_structs.h"

unsigned int	chash(char *word, int max_hash);
char			**get_env_keys(t_env_item **env, int envcount);
char			**table_to_str(t_env_item **env, int envcount);
void			print_env_strtable(t_env_item **env, int envcount);
void			print_env(t_env_item **env, int envcount);
t_env_item		*env_create_item(char **keyval, int glob);
int				env_add_item(t_env_item **env, int envcount, t_env_item *item);
int				add_item(char **keyval, t_env_item **env, int envcount, unsigned int hash);
int				env_populate(t_env_item ***genv, char **environ);

void			myexit(t_env_item ***env, int envcount, char *nu, char *msg);

int				envdup(t_env_item **env, int envcount, t_env_item ***n);
void			env_item_del(t_env_item **env, int hash);
int				envfree(t_env_item **env, int envcount);

int				menv(t_env_item **env, int envcount, char **line);
char			*mgetenv(t_env_item **env, int envcount, char *key);
t_env_item		*mgetenv_s(t_env_item **env, int envcount, char *key);
int				msetenv(t_env_item **env, int envcount, char *keyval);
int				msetenv_t(t_env_item **env, int envcount, char *key, char *val);
int				munsetenv(t_env_item **env, int envcount, char *key);
void			bi_echo(char **args);
void			ft_strtdel(char **str_t);
int				shparse(char *line, t_shcmd *cmd, t_env_item **env, int ec);
void			shell_loop(t_env_item **env, int envcount);
int				forkexec(char *cmd, char **av, t_env_item **env, int envcount);
char			*in_path(char *cmd, char *path);
char			*cin_c2c(char *c1, char **c2);
int				exec_cmd(t_shcmd *cmd, t_env_item **env, int envcount);
int				builtins(t_shcmd *cmd, t_env_item **env, int envcount);
void			sp_prompt(t_env_item **env, int envcount);
#endif
