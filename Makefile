NAME = minishell.out

SRC =   srcs/main/main.c
SRC +=  srcs/exec/exec.c srcs/util/splitline.c srcs/parse/parse.c
SRC +=	srcs/main/redirection.c
SRC +=	srcs/builtins/ft_echo.c srcs/builtins/ft_env.c srcs/builtins/ft_exit.c
SRC +=	srcs/builtins/ft_export.c srcs/builtins/ft_pwd.c srcs/builtins/ft_unset.c
SRC +=	srcs/builtins/ft_cd.c srcs/main/builtins_checker.c
SRC +=	srcs/env/env_util.c srcs/env/get_env.c srcs/env/init_env.c
SRC +=	srcs/malloc_and_free/add_list_malloc.c srcs/malloc_and_free/free_util.c
SRC +=	srcs/malloc_and_free/libft_with_list_malloc.c srcs/pipe/pipe.c
SRC +=	srcs/builtins/ft_export_util_with_args.c srcs/builtins/ft_unset_util.c
SRC +=	srcs/builtins/ft_export_util_with_noarg.c
SRC +=	srcs/parse/split_args.c srcs/util/args_util.c

FLAG =	-Wall -Werror -Wextra -Iincludes -Ilibft -g
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