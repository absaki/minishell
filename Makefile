NAME = minishell

SRC =   srcs/main/main.c
SRC +=  srcs/exec/exec.c srcs/util/splitline.c srcs/parse/parse.c
SRC +=	srcs/builtins/ft_echo.c srcs/builtins/ft_env.c srcs/builtins/ft_exit.c srcs/builtins/ft_exit_util.c
SRC +=	srcs/builtins/ft_export.c srcs/builtins/ft_pwd.c srcs/builtins/ft_unset.c
SRC +=	srcs/builtins/ft_cd.c srcs/main/init_t_sh.c srcs/builtins/ft_cd_util.c
SRC +=	srcs/env/env_util.c srcs/env/get_env.c srcs/env/init_env.c
SRC +=	srcs/malloc_and_free/add_list_malloc.c srcs/malloc_and_free/free_util.c
SRC +=	srcs/malloc_and_free/libft_with_list_malloc.c srcs/pipe/pipe.c
SRC +=	srcs/builtins/ft_export_util_with_args.c srcs/builtins/ft_unset_util.c
SRC +=	srcs/builtins/ft_export_util_with_noarg.c
SRC +=	srcs/parse/split_args.c srcs/util/args_util.c srcs/signal/signal.c
SRC +=	srcs/exec/cmdsearch.c srcs/exec/makeenvlist.c
SRC +=	srcs/parse/redirection_parse.c srcs/parse/redirection_util.c
SRC +=	srcs/exec/open_rd_file.c srcs/main/shlvl.c
SRC +=	srcs/exec/fd.c srcs/parse/dollar_util.c srcs/parse/dollar.c 

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