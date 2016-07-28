# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/11 13:41:06 by lpoujade          #+#    #+#              #
#    Updated: 2016/07/28 20:10:17 by lpoujade         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=basicshell
SRCDIR=./src
OBJDIR=./.obj

CC=clang
CFLAGS=-Wall -Werror -Wextra -g
CPPFLAGS=-Iincludes/ -Ilibft/includes

LDFLAGS=-Llibft/
LDLIBS=-lft

LIB=libft/libft.a

SRC=main.c shparse.c ft_strtdel.c access.c cmd.c builtins.c prompt.c
OBJ=$(SRC:.c=.o)

SRCS=$(addprefix $(SRCDIR)/,$(SRC))
OBJS=$(addprefix $(OBJDIR)/,$(OBJ))

# GCOV, llvm specific
# CFLAGS+=-g -fprofile-arcs -ftest-coverage
# LDFLAGS+=--coverage

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@echo "linking to\033[32m" $@ "\033[0m ... "
	@$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p .obj
	@echo "compiling\033[36m" $@ "\033[0m ..."
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIB):
	make -C libft/

clean:
	-@rm $(OBJS) && echo "deleting" $(OBJS)

doc:
	doxygen docs/dox/discover

covclean:
	-@rm $(OBJS:.o=.gcno) && echo "deleting" $(OBJS:.o=.gcno)
	-@rm $(OBJS:.o=.gcda) && echo "deleting" $(OBJS:.o=.gcda)

fclean: clean
	-@rm $(NAME) && echo "deleting" $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

