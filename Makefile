##########   BASE   ##########
# File name
NAME = philo

# Sources
SRCS += main.c
SRCS += src/errors.c
SRCS += src/thread.c
SRCS += src/routine.c
SRCS += src/actions.c
SRCS += src/init.c
SRCS += src/utils.c
SRCS += src/debug.c
SRCS += src/monitoring.c
SRCS += src/time.c

OBJS = ${SRCS:.c=.o}

HEADER += includes/philosophers.h

INCLUDES_DIR= -I ./includes/

# Compilateurs
CC = cc
CFLAGS = -fsanitize=thread -g -Wall -Wextra -Werror

##########   RULES   ##########
all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	${CC} ${SRCS} -pthread -o ${NAME} ${CFLAGS} ${INCLUDES_DIR}

%.o: %.c $(HEADER)
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re