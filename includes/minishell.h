/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 17:37:43 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/15 14:53:07 by lpoujade         ###   ########.fr       */
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

# define HASHT_SIZE 40

char		**ft_strtnew(size_t size);

unsigned int	chash(char *word, int max_hash);
char			**get_env_keys(t_env_item **env);
t_env_item		*env_create_item(char **keyval, int glob);
t_env_item		*env_new_item(char **keyval, char *keyval_in_one, int g);
int				env_add_item(t_env_item **env, t_env_item *item);
int				add_item(char **keyval, t_env_item **env, unsigned int hash);

int				menv(t_env_item *env, char **args);
void			env_print_node(t_list *m);
void			env_print(t_env_item *env);
int				env_populate(t_env_item **env, char **environ);
int				env_fake_sort(t_list *t, t_list *n);
void			env_free(t_env_item **env);
char			*mgetenv(t_env_item *env, char *key);
int				msetenv(t_env_item *env, char **keyval, char *pair, int g);
int				munsetenv(t_env_item **env, char *key);
char			**env_to_table(t_env_item *env);

void			myexit(t_env_item **env, char *nu, char *msg);

int				envdup(t_env_item **env, t_env_item ***n);
void			env_item_del(t_env_item **env, int hash);

//t_env_item		*mgetenv_s(t_env_item **env, char *key);
//int				msetenv(t_env_item **env, char *keyval);
//int				msetenv_t(t_env_item **env, char *key, char *val);
//int				munsetenv(t_env_item **env, char *key);
void			bi_echo(char **args);
int				shparse(char *line, t_shcmd *cmd, t_env_item *env);
void			shell_loop(t_env_item **env);
int				forkexec(char *cmd, char **av, t_env_item *env);
char			*in_path(char *cmd, char *path);
char			*cin_c2c(char *c1, char **c2);
int				exec_cmd(t_shcmd *cmd, t_env_item *env);
int				builtins(t_shcmd *cmd, t_env_item *env);
void			sp_prompt(t_env_item *env);
#endif
