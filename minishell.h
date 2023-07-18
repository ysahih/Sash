#ifndef MINISHELL
#define MINISHELL
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
#include <sys/wait.h>

# define PROMPT "sash"

// int	g_rd;

typedef struct s_global
{
	int	rl;
	int exit_status;
} t_global;
t_global	gl;

// enum	pipe {BEFORE, AFTER};
enum	operator {WSPACE, PIPE, VAR, WORD, SQUOTE, DQUOTE, OUTRED, INRED, APPEND, HERDOC};
				// 0      1     2     3     4       5      6                        9

// # define SC  " \t\n!%*\"'+,-./\\:;<=>?@[]~^`|$"
// # define NOTWORD " \t\r\n\"'\v\f|<>$/"

typedef struct s_lexer
{
	int		type;
	char	*str;
	struct s_lexer	*next;
	struct s_lexer *previous;	
}  t_lexer;


typedef struct	s_var
{
	char 			*key;
	char 			*val;
	struct s_var	*next;
} t_var;

typedef struct s_simple_cmds
{
	char					**str;
	int						in_fd;
	int						out_fd;
	int						err;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*previous;
} t_simple_cmd;

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
char	*ft_strcpy(char *str, int size);
int		ft_strlen(char *s);
bool	valid_var(char c);
bool	is_symbol(char c);
bool	is_digit(char c);
bool	is_alnum(char c);
bool	is_alpha(int c);
bool	valid_var(char c);


//syntax analyzer
bool	analyze_syntax(t_lexer *cmd);
bool	analyze_quote(t_lexer **node, int flag);
bool	pipe_analyze(t_lexer *cmd);
bool	pipe_checker(t_lexer *cmd, int i);


//------------------------------------------------------------------------------

typedef struct	s_export
{
	char 			*var;
	char 			*val;
	struct s_export	*next;
} t_export;

typedef struct	s_all
{
	t_var 				*env;
	t_var 				*exp;
	t_simple_cmd		*cmd;
} t_all;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;         

typedef struct s_pwd
{
	t_var			*node;
	t_var			*pwd_en;
	t_var			*oldpwd_en;
	t_var			*pwd_ex;
	t_var			*oldpwd_ex;
}	t_pwd;

//parse
int		alpha(int c);
void	parse(t_all *all, t_lexer *cmdline);

//utils
int		ft_strcmp(char *st1, char *st2);
int		ft_strchr(char *str, int ch);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *str);
t_var	*sort_env(t_var *lst);
int		arg(char *str);
t_var	*ft_last(t_var *lst);
t_var	*lstnew_exen(char  *key, char  *val);
void	add_exen_back(t_var **exen, t_var *new);
void	lst_var(t_var **var, char **s);
char	**ft_split(char *str);
char	*ft_strjoin(char *s1, char *s2);
t_var	*check_char(t_var	*env, char	*str);
void	ftputstr(char *str);
void	ft_putstr_fd(char *s, int fd);

//builtins cmds
void	env(t_all *all);
void	export(t_all *all);
void    pwd(t_all   *all);
void    echo(t_simple_cmd  *all);
t_var	*unset_env(char *str, t_var **env);
t_var	*unset_exp(char *str, t_var **exp);
void    unset(t_simple_cmd *p, t_var **env, t_var **exp);
void	cd(t_all *all);
void	ex_it(t_all *all);
void    one_cmd_nb(t_all *all, t_simple_cmd	*p);
void    one_cmd_nob(t_all *all, t_simple_cmd *p);
void	ft_putstr_fd(char *s, int fd);
int		alpha(int c);
char	**my_env(t_all *all);
// int		cd(char *str);


// execution
int		exec(t_all *all);

void	sig_handler();
void	handle_INT(int sig);
#endif
