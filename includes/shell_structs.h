/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 16:43:20 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/03 16:44:10 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_STRUCTS_H
# define SHELL_STRUCTS_H

typedef struct			s_shcmd
{
	char				*cmd;
	char				**args;
}						t_shcmd;

typedef struct			s_env_item
{
	char				*key;
	char				*value;
	int					glob: 1;
	struct s_env_item	*next;
}						t_env_item;

#endif
