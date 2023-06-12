#include "minishell.h"

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

// bool	special_char(int c)
// {
// 	return (c == '0' && c == '_' && c == '?' && c == ' ' && c == '"');
// }


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

bool	valid_var(char c)
{
	return (is_alpha(c) || is_digit(c) || c == '_');
}

char	*ft_strcpy(char *str, int size)
{
	int	i;
	char *word;

	i = 0; 
	word = malloc(size + 1);
	while (str[i] && i < size)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
