#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabdulla <aabdulla@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/07 20:38:22 by aabdulla          #+#    #+#              #
#    Updated: 2019/02/07 20:39:15 by aabdulla         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol
LIBFT = -lft -L./libft/
CFLAGS = -Wall -Werror -Wextra
OBJDIR	= ./obj/
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJ = $(addprefix $(OBJDIR),$(SRC:.c=.o))

MLX	= -lmlx -framework OpenGL -framework AppKit

SRC =	main.c \
		color.c \
		draw.c \
		fractals.c \
		fractals2.c \
		key.c \
		mouse.c \
		info.c \
		add.c \

all: obj $(NAME)

obj:
	@ mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	@ echo "compiling...\n"
	@ make -C libft/
	@ gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBVEC) -I $(INCDIR) $(MLX)
	@ echo "done\n"

$(OBJDIR)%.o:$(SRCDIR)%.c
	@ gcc $(CFLAGS) $(MLXINC) -I $(INCDIR) -c -o $@ $<

clean:
	@ make clean -C libft/
	@ /bin/rm -rf $(OBJDIR)
	@ echo "clean done"

fclean: clean
	@ make fclean -C libft/
	@ /bin/rm -f $(NAME)
	@ echo "fclean done"

re: fclean all

.PHONY: all clean fclean re