#include "../../minishell.h"

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_symbol(char c)
{
	return (c == ' ' || c == '\'' || c == '"' || c == '|'
		|| c == '<' || c == '>'|| c == '*');
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;

	while (i[s])
		i++;
	return (i);
}

bool	is_alnum(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || is_digit(c));
}

bool	is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}
