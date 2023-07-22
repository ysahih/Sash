NAME = sash

HDR = minishell.h

SRCS = main.c\
lst_utils.c\
lexer.c\
lexer_utils.c\
syntax_analyzer.c\
parse.c\
allocate.c\
execution/exec.c\
execution/utils00.c\
execution/utils01.c\
execution/env.c\
execution/export.c\
execution/export_only.c\
execution/export_egal_plus.c\
execution/export_lst-utils.c\
execution/pwd.c\
execution/echo.c\
execution/unset.c\
execution/cd.c\
execution/cd_curr_prvs.c\
execution/cd_swap_home.c\
execution/exit.c\
execution/not_builtin.c\

RM = rm -rf
CC = cc
OBJS = $(SRCS:%.c=%.o)
B_OBJS = $(B_SRCS:%.c=%.o)
CFLAGS =  -Wall -Wextra -Werror -I/Users/ysahih/Desktop/readline/include
 
RLFLAGS = -L/Users/ysahih/Desktop/readline/lib/ #-fsanitize=address -g

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(RLFLAGS) $^ -o $(NAME) -lreadline 

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJS) 

fclean : clean
	@$(RM) $(NAME) 

re : fclean all 