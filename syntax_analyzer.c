#include "minishell.h"

bool	pipe_checker(t_lexer *cmd, int i)
{
	if (i && cmd->type == WSPACE && cmd->next == NULL)
		return false;
	if (!i && cmd->type == WSPACE && cmd->previous == NULL)
		return false;
	else if (cmd->next && cmd->previous)
	{
		if (i && cmd->type == WSPACE && cmd->next)
			cmd = cmd->next;
		else if (!i && cmd->type == WSPACE && cmd->previous)
			cmd = cmd->previous;
	}
	if (i)
		return (cmd->type >= VAR && cmd->type <= HERDOC);
	return (cmd->type >= VAR && cmd->type <= DQUOTE);
}

bool	pipe_analyze(t_lexer *cmd)
{
	bool	flag;

	flag = true;
	if (cmd->next == NULL || cmd->previous == NULL)
		flag = false;
	else if (cmd->next && cmd->previous)
	{
		flag *= pipe_checker(cmd->next, 1);
		flag *= pipe_checker(cmd->previous, 0);
	}
	if (!flag){
		write (1, "error\n", 6);
		return false;
	}
	return true;
}

bool	analyze_quote(t_lexer **node, int flag)
{
	t_lexer	*cmd;

	cmd = *node;
	if (!cmd->next)
		return false ;
	cmd = cmd->next;
	while(cmd && cmd->type != flag)
		cmd = cmd->next;

	*node = cmd;
	if (!cmd)
		return false ;
	return true;
}
void	print_err(char *s)
{
	printf("sash: syntax error near unexpected token `%s'\n", s);
}

bool	analyze_syntax(t_lexer *cmd)
{
	bool flag;

	flag = true;
	while (cmd)
	{
		if (cmd->type == WSPACE && cmd->next)
			cmd = cmd->next;
		if (cmd->type == PIPE)
		{
			flag *= pipe_analyze(cmd);
			if (!flag)
				return false;
		}
		if (cmd->type >= OUTRED && cmd->type <=  HERDOC)
		{
			if (cmd->next && cmd->next->type == WSPACE)
				cmd = cmd->next;
			if (!cmd->next || cmd->next->type > DQUOTE || cmd->next->type < WORD)
			{
				if (cmd->next)
					print_err(cmd->next->str);
				else
					print_err("newline");
				return false;
			}
		}
		if (cmd->type == SQUOTE || cmd->type == DQUOTE )
		{
			if (cmd->type == SQUOTE)
			{
				flag *= analyze_quote(&cmd, SQUOTE);
				if (!flag)
					return false;
			}
			if (cmd->type == DQUOTE)
			{
				flag *= analyze_quote(&cmd, DQUOTE);
				if (!flag)
					return false;
			}
		}
		cmd = cmd->next;
	}
	return true;
}
