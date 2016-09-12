/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 16:43:20 by lpoujade          #+#    #+#             */
/*   Updated: 2016/09/12 17:00:37 by lpoujade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_STRUCTS_H
# define SHELL_STRUCTS_H

typedef struct			s_shcmd
{
	char				*cmd;
	char				**args;
}						t_shcmd;

typedef struct		s_env_item
{
	struct s_env_item	*next;
	struct s_env_item	*prev;
	char				**keyval;
	int					glob;
}					t_env_item;

#endif
