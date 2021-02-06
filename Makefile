NAME = minishell.out

SRC =   srcs/main.c
SRC +=  srcs/exec.c srcs/splitline.c srcs/parse.c

FLAG =	-Wall -Werror -Wextra -Iincludes -Ilibft
OBJ  =	$(SRC:.c=.o)
all:	$(NAME)

$(NAME):	libft-all $(OBJ)
			gcc $(OBJ) libft/libft.a -o $(NAME) $(FLAG)

%.o:	%.c
		gcc -c $(FLAG) -o $@ $^

clean: libft-clean
		rm -f $(OBJ) $(B_OBJ) screenshot.bmp

fclean: libft-fclean clean
		rm -f $(NAME)

re:     fclean all

libft-all:
		cd "$(PWD)/libft" && make bonus

libft-clean:
		cd "$(PWD)/libft" && rm -f *.o

libft-fclean:   libft-clean
		cd "$(PWD)/libft" && rm -f libft.a

.PHONY: all clean fclean re libft-all libft-clean libft-fclean