#ifndef MINISHELL
#define MINISHELL
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

enum	operator {SPACE, PIPE, VAR, WORD, OUTRED, INRED, APPEND, HERDOC, SQUOTE, DQUOTE };
				// 0      1     2     3     4       5      6                        9



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

