NAME = sash

HDR = minishell.h

SRCS = main.c\
parsing/lexer/lexer_tools.c\
parsing/lexer/lexer.c\
parsing/paser/expander.c\
parsing/paser/words.c\
parsing/paser/parser_tools.c\
parsing/paser/redirection.c\
parsing/paser/parser.c\
parsing/utils/lexer_utils00.c\
parsing/utils/lexer_utils01.c\
parsing/utils/paser_utils00.c\
utils/lst_utils.c\
utils/utils00.c\
utils/utils01.c\
utils/utils02.c\


syntax_analyzer.c\
allocate.c\
execution/exec.c\
execution/utils00.c\
execution/utils01.c\
execution/env.c\
execution/export.c\
execution/export_only.c\
execution/export_egal_plus.c\
execution/export_lst-utils.c\
execution/export_invalid.c\
execution/pwd.c\
execution/echo.c\
execution/unset.c\
execution/invalid_unset.c\
execution/cd.c\
execution/cd_curr_prvs.c\
execution/cd_swap_home.c\
execution/exit.c\
execution/not_builtin.c\
execution/notbuiltin_utils0.c\
execution/notbuiltin_utils1.c\

RM = rm -rf
CC = cc
OBJS = $(SRCS:%.c=%.o)
B_OBJS = $(B_SRCS:%.c=%.o)
CFLAGS = -I/Users/ysahih/Desktop/readline/include
 
RLFLAGS = -L/Users/ysahih/Desktop/readline/lib/

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(RLFLAGS) $^ -o $(NAME) -lreadline -lhistory

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJS) 

fclean : clean
	@$(RM) $(NAME) 

re : fclean all