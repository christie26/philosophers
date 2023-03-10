SRCS		= 	main.c \
				philo_setup.c \
				philo_utils.c \
				philosophers.c

OBJS		:= $(SRCS:%.c=%.o)

SRC_DIR		= ./src/
SRCS		:= $(addprefix $(SRC_DIR), $(SRCS))

OBJ_DIR 	= ./obj/
OBJS		:= $(addprefix $(OBJ_DIR), $(OBJS))

NAME		= ./philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -fsanitize=thread
RM			= rm -f

all:		${NAME}

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

$(NAME): 	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) 

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
