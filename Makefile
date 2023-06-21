NAME = sash

HDR = minishell.h

SRCS = main.c\
lst_utils.c\
lexer.c\
lexer_utils.c\
syntax_analyzer.c\
parse.c\
execution/exec.c\
execution/utils.c\
execution/env.c\
execution/export.c\
execution/pwd.c\
execution/echo.c\

RM = rm -rf
CC = cc
OBJS = $(SRCS:%.c=%.o)
B_OBJS = $(B_SRCS:%.c=%.o)
CFLAGS = -Wall -Wextra -Werror 
# -fsanitize=address -g


all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^ -lreadline

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJS) 

fclean : clean
	@$(RM) $(NAME) 

re : fclean all 