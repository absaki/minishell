# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kikeda <kikeda@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/23 16:25:43 by kikeda            #+#    #+#              #
#    Updated: 2021/02/24 13:49:31 by kikeda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c
SRC +=	ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c
SRC += ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c
SRC += ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c
SRC += ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c
SRC += ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c
SRC += ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c
SRC += ft_putnbr_fd.c ft_strcmp.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c
BONUS += ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c
BONUS += ft_lstmap.c ft_nsplit.c ft_isnumstr.c ft_lstnewdup.c
BONUS += ft_free_and_del.c

FLAG =	-Wall -Werror -Wextra
OBJ  =	$(SRC:.c=.o)
B_OBJ = $(BONUS:.c=.o)
all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	gcc -c $(FLAG) -o $@ $^

clean:
	rm -f $(OBJ) $(B_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all $(B_OBJ)
	ar rcs $(NAME) $(OBJ) $(B_OBJ)

.PHONY: all bonus clean fclean re
