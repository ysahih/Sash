#include "minishell.h"

void	builtin_cmds(char *s)
{
	if (!strcmp(s, "exit"))
		exit(0); 
}


bool	is_symbol(char c)
{
	return (c == ' ' && c == '\'' && c == '"' && c == '|' && c == '<' && c == '>'&& c == '*');
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (i[s])
		i++;
	return (i);
}


char	*ft_strcpy(char *str, int size)
{
	int	i;
	char *word;

	i = 0;
	word = malloc(size + 1);
	while (str[i] != '\0' && i < (size -1))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}	


void	tokenize_word(t_tokenize **node, char *s)
{
	char *cmd;
	int	i;

	i = 0;
	while (*s && !is_symbol(*s))
		s++;
	cmd = ft_strcpy(s, i);
	create_node(node, cmd, WORD);
}

void	tokenize(char *str)
{
	char	*wp;
	char *line;
	t_tokenize *node = NULL;

	line = str;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line == '|')
			create_node(&node, "|", PIPE);
		if (*line == '>')
		{
			if (*line + 1 == '>')
				create_node(&node, ">>", APPEND);
			else
				create_node(&node, ">", OUTRED);
		}
		if (*line == '<')
		{
			if (*line + 1 == '<')
				create_node(&node, "<<", HERDOC);
			else
				create_node(&node, "<", INRED);
		}
		else
			tokenize_word(&node, str);
		line++;
	}
	
	while (node)
	{
		printf("%s\n", node->str);
		node = node->next;
	}
}

int	main(int ac, char **av)
{
	char	*line;

	if (ac != 1)
		return (printf("program does not accept agruments"), 0);
	while (1)
	{
		line = readline("sh$ ");
		if (!line)
			break ;
		// builtin_cmds(line);
		tokenize(line);


		if (*line)
			add_history(line);
	}
}