#ifndef MINISHELL
#define MINISHELL
#include <readline/readline.h>
#include <readline/history.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <stdbool.h>

enum	operator {SPACE, PIPE, VAR, WORD, OUTRED, INRED, APPEND, HERDOC, SQUOTE, DQUOTE };

# define SC  " \t\n!%*\"'+,-./\\:;<=>?@[]~^`|$"
# define NOTWORD " \t\r\n\"'\v\f|<>$/"


# define SC  " \t\n!%*\"'+,-./\\:;<=>?@[]~^`|$"
# define NOTWORD " \t\r\n\"'\v\f|<>$/"
typedef struct s_tokenize
{
	int		type;
	char	*str;
	struct s_tokenize	*next;
	struct s_tokenize *previous;
}  t_tokenize;

void   create_node(t_tokenize	**lst, char *s, int operator);

#endif

