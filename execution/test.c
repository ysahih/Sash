#include "../minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (i[s])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	size_t	len;
	char	*p;
	int		i;

	len = ft_strlen(str);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (str[i])
	{
		p[i] = str[i];
		i++;
	}
	return (p);
}

int main()
{
    printf("%s\n",ft_strdup(""));
}