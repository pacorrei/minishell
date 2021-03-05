NAME = minishell

all: ${NAME}

CFLAGS = -Wall -Werror -Wextra -fsanitize=address

CC = gcc

RM = rm -rf

HEAD = -I include/


SRCS_PATH = srcs/

OBJS_PATH = objs/

SRCS_NAME = main.c get_next_line.c get_next_line_utils.c ft_pwd.c ft_env.c ft_cd.c\

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	mkdir $(OBJS_PATH) 2> /dev/null || true
	gcc -c $(FLAGS) $(HEAD) -o $@ -c $<

$(NAME):  ${OBJS}
		${CC} ${CFLAGS} ${SRCS} ${HEAD} -o ${NAME}

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re :	fclean all

.PHONY: all clean fclean re
