# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/03/23 16:54:31 by ythollet     #+#   ##    ##    #+#        #
#    Updated: 2018/03/23 16:54:35 by ythollet    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

CFLAGS = -c -Wall -Wextra -Werror

NAME = ft_ls

DIR_LIB = Libft
DIR_INC = Include
DIR_SRC = Sources
DIR_OBJ = Objects

SRCS = 	ls_fillelem.c \
        ls_list.c \
        ls_getinfo.c \
        ls_print.c \
        ls_clmn.c \
        main.c

OBJS = $(addprefix $(DIR_OBJ)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
		@make -C $(DIR_LIB)
		@gcc -o $(NAME) $(OBJS) -L $(DIR_LIB) -lft

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
		@mkdir -p $(DIR_OBJ)
		@gcc -o $@ -c $< -I $(DIR_INC)

clean:
		@rm -rf $(DIR_OBJ)
		@make clean -C $(DIR_LIB)

fclean: clean
		@rm -f $(NAME)
		@make fclean -C $(DIR_LIB)

re: fclean all
