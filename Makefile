# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/22 11:05:13 by florian           #+#    #+#              #
#    Updated: 2017/10/13 08:14:05 by fpasquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= n-puzzle

SRC_NAME		= main.c check_argv.c gestion_file.c gestion_grid.c				\
				  functions_dfs.c solve_npuzzle.c moves.c show_mlx.c			\
				  functions_events.c draw_grid.c functions_show_moves.c			\
				  gestion_weight.c functions_weight.c solvable.c generate_grid.c\
				  functions_weight2.c check_file.c moves2.c heuristics.c		\
				  check_doublon.c

SRC_GENERATOR	= puzzle_generator.c puzzle_generator2.c

INC_GENERATOR	= puzzle_generator.h

INCLUDES		= npuzzle.h

LIBRARY			= libft/libft.a

OTHERS			= libft Makefile auteur
ARCH			= 64
OTHER_FLAGS 	= -I /usr/X11/include -l mlx -framework OpenGL -framework AppKit

GCC				= gcc
CFLAGS			= -Wall -Wextra -Werror -o3
OBJ_NAME		= $(SRC_NAME:.c=.o)

SRCDIR			= srcs
OBJDIR			= objs
INCDIR			= incs

SRC				= $(addprefix $(SRCDIR)/, $(SRC_NAME))
SRC_GEN			= $(addprefix $(SRCDIR)/, $(SRC_GENERATOR))
OBJ				= $(addprefix $(OBJDIR)/, $(OBJ_NAME))
INC				= $(addprefix $(INCDIR)/, $(INCLUDES))
DATE			= `date +'%d/%m/%y %H:%M:%S'`

All : $(NAME)

$(NAME) :  $(LIBRARY) $(OBJDIR) $(OBJ)
	$(GCC) $(CFLAGS) $(OTHER_FLAGS) -m$(ARCH) -o $(NAME) $(OBJ) $(LIBRARY)
	$(GCC) $(CFLAGS) $(LIBRARY) -o grid_generator $(SRC_GEN)
	@echo "\033[0;32m"$(NAME) "DONE\033[0m"

$(LIBRARY) :
	@echo "\033[0;32mCOMPILE LIBFT ${ARCH}\033[0m"
	make -C libft libft$(ARCH)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INC)
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -m$(ARCH) -o $@ -c $<

$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM
	rm -rf $(OBJDIR)
	rm -rf grid_generator
	rm -rf grid
	make -C libft fclear

re : fclean All

norm:
	norminette $(SRC) $(INC)
