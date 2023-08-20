SRCS = main_mlx_test.c



OBJS			= $(SRCS:.c=.o)
CC				= cc
RM				= rm -f
GLFW = $(shell brew --prefix glfw)
MLX_FLAG = ./MLX42/build/libmlx42.a -Iinclude -lglfw -L $(GLFW)/lib/ -framework Cocoa -framework OpenGL -framework IOKit
LIBS            = -Wall -Wextra -Werror -fsanitize=address -g
NAME			= cube3D


%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@

all:		cube_3d_logo	$(NAME) 

$(NAME):	cube_3d_logo	$(OBJS)
			@cc $(LIBS) $(OBJS) $(MLX_FLAG) -o $(NAME)
			@echo "\033[92m\033[92m✅cube3D GENERATED YOU CAN STARTED✅\033[0m"
			@echo "\033[92m🎮 USE ./cube3D <MAP FILE NAME> 🎮"
clean:
				@$(RM) $(OBJS) 
				@echo "\033[92m\033[31m Delete object files🗑\033[31m"
			
fclean:			clean
				@$(RM) $(NAME)
				@echo "\033[92m\033[31m Delete exucted file🗑\033[31m"

re:				fclean $(NAME)

cube_3d_logo:

	@echo "\033[92m ██████╗██╗   ██╗██████╗ ███████╗\033[0m██████╗ ██████╗"
	@echo "\033[92m██╔════╝██║   ██║██╔══██╗██╔════╝\033[0m╚════██╗██╔══██╗"
	@echo "\033[92m██║     ██║   ██║██████╔╝█████╗  \033[0m █████╔╝██║  ██║"
	@echo "\033[92m██║     ██║   ██║██╔══██╗██╔══╝  \033[0m ╚═══██╗██║  ██║"
	@echo "\033[92m╚██████╗╚██████╔╝██████╔╝███████ \033[0m██████╔╝██████╔╝"
	@echo "\033[92m ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝\033[0m╚═════╝ ╚═════╝"
	@echo "\033[92mCREATING .O FILES AND SO_LONG⌛\033[0m"


.PHONY: all fclean clean re cube_3d_logo
