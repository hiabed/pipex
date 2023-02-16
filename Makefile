NAME = pipex

CFILES = pipex.c errors_handler.c ./libft/ft_split.c ./libft/ft_strjoin.c ./libft/ft_strncmp.c
		 
OBJECT = ${CFILES:.c=.o}
CFLAGS = -Wall -Wextra -Werror
CC = cc

all : ${NAME}

${NAME} : ${OBJECT}
	${CC} ${CFILES} -o ${NAME} 

clean :
	${RM} ${OBJECT}

fclean : clean
	${RM} ${NAME}

re : fclean all