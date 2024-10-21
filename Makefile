NAME				= 	minishell

CC					=	cc
FLAGS				=   -Wextra -Wall -Werror 

SRCS_MAIN			= 	src/main.c				\
						src/main_helper.c		\
						src/builtin.c 			\
						src/builtin2.c 			\
						src/history_stuff.c 	\
						src/var_stuff.c 		\
						src/export_builtin.c 	\
						src/redirect_in.c		\
						src/redirect_out.c		\
						src/execute.c			\
						src/parse.c				\
						src/pipe1.c				\
						src/exec_utils.c 		\
						src/here_doc.c	 		\
						src/free.c				\
						src/util.c				\
						src/signals.c			\

LIBFT 				=	tools/libft/libft.a

OBJ 				=	tools/obj
OBJ_MAIN			=	$(SRCS_MAIN:src/%.c=$(OBJ)/%.o)

all:						$(NAME)

$(LIBFT):
				@cd tools/libft && make -s && make bonus -s

$(NAME):$(LIBFT) $(OBJ_MAIN)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_MAIN) -L./tools/libft -lft -lreadline

$(OBJ)/%.o:	src/%.c
			@cd tools
			@mkdir -p $(OBJ)
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -rf $(OBJ)/*
			@cd tools/libft && make clean -s


fclean: 			clean
			@rm -rf $(NAME)
			@rm -rf $(OBJ)
			@cd tools/libft && make fclean  -s

re:			fclean all

.PHONY:		all clean fclean re
