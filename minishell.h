#ifndef MINISHELL
#define MINISHELL
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

enum	pipe {BEFORE, AFTER};
enum	operator {SPACE, PIPE, VAR, WORD, SQUOTE, DQUOTE, OUTRED, INRED, APPEND, HERDOC};
				// 0      1     2     3     4       5      6                        9


# define SC  " \t\n!%*\"'+,-./\\:;<=>?@[]~^`|$"
# define NOTWORD " \t\r\n\"'\v\f|<>$/"

typedef struct s_lexer
{
	int		type;
	char	*str;
	struct s_lexer	*next;
	struct s_lexer *previous;
}  t_lexer;




//list utils
void	create_node(t_lexer	**lst, char *s, int operator);
void	ft_lstadd_back(t_lexer **lst, t_lexer *new);
t_lexer	*ft_lstlast(t_lexer *lst);


//lexer
t_lexer	*tokenize(char *line);
void	tokenize_word(t_lexer **node, char **s);
void	tokenize_var(t_lexer **node, char **s);
void	tokenize_dquote(t_lexer **node, char **s);
void	tokenize_squote(t_lexer **node, char **s);
void	tokenize_red(t_lexer **node, char **s);

//lexer utils
char	*ft_strcpy(char *str, int size);
bool	valid_var(char c);

bool	is_symbol(char c);
bool	is_digit(char c);
int		ft_strlen(char *s);
bool	is_alnum(char c);
bool	is_alpha(int c);
bool	valid_var(char c);
char	*ft_strcpy(char *str, int size);


//syntax analyzer
bool	analyze_syntax(t_lexer *cmd);
bool	analyze_quote(t_lexer **node, int flag);
bool	pipe_analyze(t_lexer *cmd);
bool	pipe_checker(t_lexer *cmd, int i);


#endif

