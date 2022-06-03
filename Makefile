NAME = minishell
SRCS = ./src/*.c
RM = rm -f

LIBFT_PATH 		= ./libft
LIBFT			= $(LIBFT_PATH)/libft.a
MAKELIB 		= make -C $(LIBFT_PATH) 

all:
	$(MAKELIB)
	gcc $(SRCS) $(LIBFT) -o $(NAME) -lreadline

fclean:
	$(RM) $(NAME)
	$(MAKELIB) fclean

clean:
	$(RM) $(NAME)

re: clean all

do: all
	./$(NAME)