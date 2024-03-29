SRCS		= 	main.c \
				utils1.c \
				utils2.c \
				philo_setup.c \
				philo_routine.c \
				philo_utils.c

OBJS		:= $(SRCS:%.c=%.o)

SRC_DIR		= ./src/
SRCS		:= $(addprefix $(SRC_DIR), $(SRCS))

OBJ_DIR 	= ./obj/
OBJS		:= $(addprefix $(OBJ_DIR), $(OBJS))

NAME		= ./philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -g3 -fsanitize=thread
RM			= rm -f

all:		${NAME}

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME): 	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

sani: 		$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) 

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
