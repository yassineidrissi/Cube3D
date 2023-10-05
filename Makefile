NAME		= cub3D
NAME_BONUS	= cub3D_BONUS
CC			= cc
RM			= rm -f
GLFW		= $(shell brew --prefix glfw)
MLX_FLAG	= ~/MLX42/build/libmlx42.a -I ~/MLX42/include -Iinclude -lglfw -L $(GLFW)/lib/ -framework Cocoa -framework OpenGL -framework IOKit
LIBS		= -Wall -Wextra -Werror -fsanitize=address -g

SRCS =	main.c ./srcs/ft_strjoin.c ./srcs/error.c ./srcs/ft_atoi.c ./srcs/ft_itoa.c ./srcs/ft_printf.c ./srcs/ft_split.c ./srcs/ft_strdup.c \
		./srcs/get_next_line.c ./srcs/get_next_line_utils.c ./srcs/ft_strtrim.c ./srcs/ft_substr.c ./validation/validation.c ./validation/validation2.c \
		./validation/check_content.c ./validation/fill_type.c ./validation/validation3.c ./config/config_utils.c ./config/ft_hook.c ./config/drawing.c \
		./math_stuff/start.c ./math_stuff/start_utils.c ./math_stuff/txtur_colors.c ./math_stuff/put_texture.c

SRCS_BONUS =	main_bonus.c ./srcs/ft_strjoin.c ./srcs/error.c ./srcs/ft_atoi.c ./srcs/ft_itoa.c ./srcs/ft_printf.c ./srcs/ft_split.c ./srcs/ft_strdup.c \
				./srcs/get_next_line.c ./srcs/get_next_line_utils.c ./srcs/ft_strtrim.c ./srcs/ft_substr.c ./validation/validation.c ./validation/validation2.c \
				./validation/check_content_bonus.c ./validation/fill_type.c ./validation/validation3.c ./config/config_utils.c ./config/ft_hook.c ./config/drawing_bonus.c \
				./math_stuff/start_bonus.c ./math_stuff/start_utils_bonus.c ./math_stuff/txtur_colors.c ./math_stuff/put_texture.c

OBJS			= $(SRCS:.c=.o)
OBJS_BONUS		= $(SRCS_BONUS:.c=.o)


%.o : %.c 
		@$(CC) $(CFLAGS) -I ~/MLX42/include -c $< -o $@

all:		cube_3d_logo	$(NAME) 

$(NAME):	cube_3d_logo	$(OBJS)
			@cc $(LIBS) $(OBJS) $(MLX_FLAG) -o $(NAME)
			@echo "\033[92m\033[92m✅cub3D GENERATED YOU CAN STARTED✅\033[0m"
			@echo "\033[92m🎮 USE ./cub3D <MAP FILE NAME> 🎮"

bonus:		cube_3d_logo	$(OBJS_BONUS)
			@cc $(LIBS) $(OBJS_BONUS) $(MLX_FLAG) -o $(NAME_BONUS)
			@echo "\033[92m\033[92m✅cub3D GENERATED YOU CAN STARTED✅\033[0m"
			@echo "\033[92m🎮 USE ./cub3D <MAP FILE NAME> 🎮"

clean:
				@$(RM) $(OBJS)
				@$(RM) $(OBJS_BONUS)
				@echo "\033[92m\033[31m Delete object files🗑\033[31m"
			
fclean:			clean
				@$(RM) $(NAME)
				@$(RM) $(NAME_BONUS)
				@echo "\033[92m\033[31m Delete exucted file🗑\033[31m"

re:				fclean all

test: re
				@echo "\033[92m\033[31m 🪄TESTING MAP1🪄\033[31m"
				@./cub3D ./maps/map1.cub
testb: fclean bonus
				@echo "\033[92m\033[31m🪄 TESTING MAP2🪄\033[31m"
				@./cub3D_BONUS ./maps/map1.cub


cube_3d_logo:

	@echo "\033[92m ██████╗██╗   ██╗██████╗ ███████╗\033[0m██████╗ ██████╗"
	@echo "\033[92m██╔════╝██║   ██║██╔══██╗██╔════╝\033[0m╚════██╗██╔══██╗"
	@echo "\033[92m██║     ██║   ██║██████╔╝█████╗  \033[0m █████╔╝██║  ██║"
	@echo "\033[92m██║     ██║   ██║██╔══██╗██╔══╝  \033[0m ╚═══██╗██║  ██║"
	@echo "\033[92m╚██████╗╚██████╔╝██████╔╝███████ \033[0m██████╔╝██████╔╝"
	@echo "\033[92m ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝\033[0m╚═════╝ ╚═════╝"
	@echo "\033[92m⌛CREATING .O FILES AND cub3D⌛\033[0m"


.PHONY: all fclean clean re cube_3d_logo
