NAME = pipex
CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
LIBFTDIR = 42libft/
SRC_DIR = src/

SRC_1 = src/pipex.c \

SRC_2 =	src/utils.c \
		src/safe.c \
			
OBJ_1 = ${SRC_1:.c=.o}
OBJ_2 = ${SRC_2:.c=.o}

INCLUDE = -L $(LIBFTDIR) -lft

${NAME}: ${OBJ_1} ${OBJ_2}
	make -C $(LIBFTDIR)
	${CC} ${FLAGS} ${OBJ_1} ${OBJ_2} -o ${NAME} ${INCLUDE}

all: ${NAME} 

clean:
	${RM} ${OBJ_1} ${OBJ_2}
	@cd $(LIBFTDIR) && $(MAKE) clean

fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) fclean

re: clean all

.PHONY: all clean fclean re bonus