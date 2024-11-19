CFLAGS = -Wall -Wextra -Werror 

CC = cc #-fsanitize=address -g3
LFLAGS = -lreadline
NAME = minishell

SRCS  = $(wildcard externel_folder/libftt/*.c) \
        $(wildcard externel_folder/gnl/*.c) \
		$(wildcard parsing/tokens/*.c) \
        $(wildcard parsing/parser/*.c) \
        $(wildcard parsing/signal/*.c) \
        $(wildcard parsing/minishel_utils/*.c) \
        $(wildcard parsing/generate_struct/*.c) \
        $(wildcard execution/builtins/export/*.c ) \
        execution/builtins/cd/cd.c \
		execution/builtins/echo/echo.c \
       	execution/builtins/env/env.c \
        execution/builtins/exit/exit.c \
        execution/builtins/pwd/pwd.c \
        execution/builtins/unset/unset.c \
        mnsh.c \
        $(wildcard execution/exec/*.c) \
        execution/builtins/builtins.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)

%.o: %.cmake
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all