NAME		:=	libft.a
INCL 		:=	-I./includes
CFLAGS		:=	-Wall -Wextra -Werror
CC			:=	cc

OBJ			:=	obj

LIBFT_DIR	:=	libft
LIBFT_SRC	:=	$(wildcard $(LIBFT_DIR)/*.c)
LIBFT_OBJ	:=	$(LIBFT_SRC:$(LIBFT_DIR)/%.c=$(OBJ)/%.o)

GNL_DIR		:=	gnl
GNL_SRC		:=	$(wildcard $(GNL_DIR)/*.c)
GNL_OBJ		:=	$(GNL_SRC:$(GNL_DIR)/%.c=$(OBJ)/%.o)

GC_DIR		:=	gc
GC_SRC		:=	$(wildcard $(GC_DIR)/*.c)
GC_OBJ		:=	$(GC_SRC:$(GC_DIR)/%.c=$(OBJ)/%.o)

PRINTF_DIR	:=	printf
PRINTF_SRC	:=	$(wildcard $(PRINTF_DIR)/*.c)
PRINTF_OBJ	:=	$(PRINTF_SRC:$(PRINTF_DIR)/%.c=$(OBJ)/%.o)

$(NAME): $(PRINTF_OBJ) $(LIBFT_OBJ) $(GNL_OBJ) $(GC_OBJ)
	ar rcs $(NAME) $(PRINTF_OBJ) $(LIBFT_OBJ) $(GNL_OBJ) $(GC_OBJ)

$(OBJ)/%.o: $(PRINTF_DIR)/%.c
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(LIBFT_DIR)/%.c
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(GC_DIR)/%.c
	@mkdir -p $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
