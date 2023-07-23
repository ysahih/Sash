#include "../../minishell.h"

bool	valid_var(char c)
{
	return (is_alpha(c) || c == '_');
}

bool	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' ||
		c == '\n' || c == '\r'  || c == '\f');
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

char	*ft_strncpy(char *s, char *s2, int len)
{
	int	i;

	i = 0;
	while (i < len && s2[i])
	{
		s[i] = s2[i];
		i++;
	}
	s[len] = '\0';
	return (s);
}
char	**ft_split(char *str)
{
	char	**s;
	int		i;
	int		j;
	int		a;

	s = malloc((sizeof(char *)) * (count_len(str)));
	if (!s)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == '=')
			i++;
		a = i;
		while (str[i] && str[i] != '=')
			i++;
		if (i > a)
			s[j++] = ft_strncpy(malloc (i - a + 1), str + a, i - a);
	}
	s[j] = NULL;
	return (s);
}