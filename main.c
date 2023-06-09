#include "minishell.h"

void	builtin_cmds(char *s)
{
	if (!strcmp(s, "exit"))
		exit(0); 
}


bool	is_symbol(char c)
{
	return (c == ' ' || c == '\'' || c == '"' || c == '|' || c == '<' || c == '>'|| c == '*');
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
	while (str[i] && i < size)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';

	return (word);
}	


void	tokenize_word(t_tokenize **node, char **s)
{
	int	i;

	char *tmp;

	tmp = *s;
	i = 0;
	
	while (tmp[i] && !is_symbol(tmp[i]))
		i++;
	
	create_node(node, ft_strcpy(*s, i), WORD);
	// printf("+%s+\n", *s + i);
	*s += i;
}

void	tokenize(char *line)
{
	t_tokenize *node = NULL;

	
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line == '|')
		{
			create_node(&node, "|", PIPE);
			line++;
		}
		else if (*line == '>')
		{
			if (*(line + 1) == '>' && *(line + 1) != '\0')
			{
				create_node(&node, ">>", APPEND);
				line++;
			}
			else
				create_node(&node, ">", OUTRED);
			line++;
		}
		else if (*line == '<')
		{
			if (*(line + 1) == '<' && *(line + 1) != '\0')
			{
	
				create_node(&node, "<<", HERDOC);
				line++;
			}
			else
				create_node(&node, "<", INRED);
			line++;
		}
		else
			tokenize_word(&node, &line);
	}
		// printf("+%s+\n", line);
	
	// printf("%s\n", (node)->str);
	while (node)
	{
		printf("-----%s-----\n", node->str);
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