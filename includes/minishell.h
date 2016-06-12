/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 11:19:44 by lpoujade          #+#    #+#             */
/*   Updated: 2016/06/12 12:28:14 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stddef.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"

int		bi_cd(char **av);
int		env(char **av);
void	sp_prompt(void);
int		command(char *line);
char	*in_path(char *cmd, char *path);
char	*cin_c2c(char *c1, char **c2);

#endif
